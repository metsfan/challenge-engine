#include <Engine/Challenge.h>
#include <Engine/Font/UnicodeRanges.h>
#include "TextFieldView.h"

namespace challenge
{
	static const int kCursorDuration = 500;
	static const int kKeyPressDuration = 500;
	static const int kKeyRepeatInterval = 50;
	static const char kBackspaceKey = 8;

	TextFieldView::TextFieldView(Frame frame) :
		FormElement(frame),
		mTextLabel(new LabelView(Frame(0, 0, frame.size.width, frame.size.height))),
		mCursor(new View(Frame(0, 1, 3, frame.size.height - 2))),
		mCursorActive(false),
		mCursorTime(0),
		mCursorPosition(1),
		mCursorIndex(0),
		mKeyPressTime(0),
		mKeyPressed(false)
	{
		this->SetBackgroundColor(Color(255, 255, 255, 255));

		this->AddKeyboardEvent(KeyboardEventKeyDown, [this](View *sender, const KeyboardEvent &e) {
			mKeyPressed = true;

			this->KeyPressed(e);
		});

		this->AddKeyboardEvent(KeyboardEventKeyPress, [this](View *sender, const KeyboardEvent &e) {
			// Do nothing, just capture the event so others can't.

			if (mKeyPressTime > kKeyPressDuration &&
				mKeyRepeatTime > kKeyRepeatInterval) {
				this->KeyPressed(e);
				mKeyRepeatTime = 0;
			}
		});

		this->AddKeyboardEvent(KeyboardEventKeyUp, [this](View *sender, const KeyboardEvent &e) {
			// Do nothing, just capture the event so others can't.
			mKeyPressTime = 0;
			mKeyRepeatTime = 0;
			mKeyPressed = false;
		});

		this->AddMouseEvent(MouseEventMouseDown, [this](View *sender, const MouseEvent &e) {
			this->JumpCursor(e);
		});

		this->AddInternalSubview(mTextLabel);

		mCursor->SetBackgroundColor(Color(0, 0, 0, 255));
		mTextLabel->AddSubview(mCursor);

		mLetterPositions.push_back(mCursorPosition);
		
		this->ClipSubviews(true);

		this->SetBorderColor(Color::Black());
		this->SetBorderWidth(1);
	}

	TextFieldView::~TextFieldView()
	{
	}

	void TextFieldView::SetText(const std::string &text)
	{
		mTextLabel->SetText(text);
	}

	void TextFieldView::Update(int deltaMillis)
	{
		mCursor->SetHeight(this->GetHeight() - 2);

		if (this->IsFocused()) {
			mCursorTime += deltaMillis;
			if (mCursorTime > kCursorDuration) {
				mCursorActive = !mCursorActive;
				mCursorTime = 0;
			}

			mCursor->SetVisible(mCursorActive);
			mCursor->SetX(mCursorPosition-2);
		}
		else {
			mCursorTime = 0;
			mCursor->SetVisible(false);
		}

		Size textDims = mTextLabel->GetFont()->GetStringDimensions(mTextLabel->GetText());
		if (textDims.width > this->GetWidth()) {
			if (mCursorIndex == mLetterPositions.size() - 1) {
				mTextLabel->SetX(this->GetWidth() - textDims.width);
			}
		}
		else {
			mTextLabel->SetX(0);
		}

		if (mKeyPressed) {
			mKeyPressTime += deltaMillis;

			if (mKeyPressTime > kKeyPressDuration) {
				mKeyRepeatTime += deltaMillis;
			}
		}

		View::Update(deltaMillis);
	}

	void TextFieldView::Render(IGraphicsDevice *device, RenderState &state, const Frame &parentFrame)
	{
		View::Render(device, state, parentFrame);
	}

	void TextFieldView::KeyPressed(const KeyboardEvent &e)
	{
		const Frame &frame = this->GetFrame();
		unsigned char c = e.keyCode;
		if(!e.shiftDown) {
			c = tolower(c);
		}
		std::string text = mTextLabel->GetText();

		if(c == kBackspaceKey) {
			if(mCursorIndex > 0) {
				mCursorIndex--;
			
				Size letterSize = mTextLabel->GetFont()->GetStringDimensions(std::string(1, text[mCursorIndex]));

				int newPosition = 0;
				for(int i = 0; i < mCursorIndex; i++) {
					newPosition += mLetterPositions[i];
				}
				mCursorPosition -= mLetterPositions[mCursorIndex];
				
				mLetterPositions.erase(mLetterPositions.begin() + mCursorIndex);
				text.erase(text.begin() + mCursorIndex);
			}
		}
		else if (LATIN_RANGE.Contains(c)) {
			text.insert(text.begin() + mCursorIndex, c);

			Size letterSize = mTextLabel->GetFont()->GetStringDimensions(std::string(1, c));
			mCursorPosition += letterSize.width;
			
			mCursorIndex++;
			mLetterPositions.insert(mLetterPositions.begin() + mCursorIndex, letterSize.width);
		}

		mTextLabel->SetText(text);

		if (mCursor->GetX() > mTextLabel->GetWidth()) {
			mTextLabel->SetX(mTextLabel->GetX() - 50);
			mTextLabel->SetWidth(mTextLabel->GetWidth() + 50);
		}
	}

	void TextFieldView::JumpCursor(const MouseEvent &e)
	{
		if(mLetterPositions.size() > 0) {
			int minDif = kInfinity;
			int minIndex = 0;

			int position = 0;
			Point labelWindowPos = mTextLabel->GetPositionInView(Point(0, 0), this->GetWindow());
			int mousePos = e.position.x - labelWindowPos.x;

			for(int i = 0; i < mLetterPositions.size(); i++) {
				if (position + (mLetterPositions[i] * 0.5) > mousePos) {
					break;
				}

				position += mLetterPositions[i];
				minIndex = i;
			}

			mCursorPosition = position;
			mCursorIndex = minIndex;
		}
	}

	void TextFieldView::ParseFromXML(XMLNode &node)
	{
		View::ParseFromXML(node);

		this->SetText(node.GetAttributeString("text"));
	}
};