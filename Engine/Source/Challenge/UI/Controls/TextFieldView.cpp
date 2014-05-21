#include <Challenge/Challenge.h>
#include <Challenge/Font/UnicodeRanges.h>
#include <Challenge/Font/TextUtil.h>
#include "TextFieldView.h"

namespace challenge
{
	static const int kCursorDuration = 500;
	static const int kKeyPressDuration = 500;
	static const int kKeyRepeatInterval = 50;
	static const char kBackspaceKey = 8;

	static const int kLetterPadding = 1;

	TextFieldView::TextFieldView(Frame frame) :
		FormElement(frame),
		mTextLabel(new LabelView(Frame(0, 0, frame.size.width, frame.size.height))),
		mCursor(new View(Frame(0, 1, 1, frame.size.height - 2))),
		mCursorActive(false),
		mCursorTime(0),
		mCursorPosition(2),
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
		mTextLabel->SetBackgroundColor(Color::Clear());

		//mLetterPositions.push_back(mCursorPosition);
		
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

			mCursor->SetAlpha(mCursorActive);
			mCursor->SetX(mCursorPosition);
		}
		else {
			mCursorTime = 0;
			mCursor->SetAlpha(0);
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
		FormElement::Render(device, state, parentFrame);
	}

	void TextFieldView::ResetCursor()
	{
		mCursorPosition = 2;
		mTextLabel->SetX(0);
	}

	void TextFieldView::KeyPressed(const KeyboardEvent &e)
	{
		const Frame &frame = this->GetFrame();
		unsigned char c = e.keyCode;
		if(e.shiftDown) {
			c = toupper(c);
		}
		else {
			c = tolower(c);
		}

		std::string text = mTextLabel->GetText();

		int newOffset = 0;

		if(c == kBackspaceKey) {
			if(mCursorIndex > 0) {
				
			
				Size letterSize = TextUtil::SizeOfText(StringUtil::ToWide(text.substr(mCursorIndex, 1)), mTextLabel->GetFont());

				int newPosition = 0;
				/*for(int i = 0; i < mCursorIndex; i++) {
					newPosition += mLetterPositions[i];
				}*/
				mCursorIndex--;

				newOffset = -mLetterPositions[mCursorIndex];

				mLetterPositions.erase(mLetterPositions.begin() + mCursorIndex);
				text.erase(text.begin() + mCursorIndex);
				
			}
		}
		else if (LATIN_RANGE.Contains(c)) {
			text.insert(text.begin() + mCursorIndex, c);

			Size letterSize = TextUtil::SizeOfText(StringUtil::ToWide(std::string(1, c)), mTextLabel->GetFont());
			newOffset = letterSize.width;

			mLetterPositions.insert(mLetterPositions.begin() + mCursorIndex, letterSize.width);
			
			mCursorIndex++;
		}

		mCursorPosition += newOffset;
		mTextLabel->SetText(text);

		Size textDims = TextUtil::SizeOfText(StringUtil::ToWide(mTextLabel->GetText()), mTextLabel->GetFont());
		mTextLabel->SetWidth(textDims.width);

		if (textDims.width > this->GetWidth() && 
			((mCursorPosition + mTextLabel->GetX()) > this->GetWidth() ||
			(mCursorPosition + mTextLabel->GetX()) < 0)) {
			mTextLabel->SetX(mTextLabel->GetX() - (50 * glm::sign(newOffset)));
			//mTextLabel->SetWidth(mTextLabel->GetWidth() + 50);
		}
		else if (textDims.width < this->GetWidth()) {
			mTextLabel->SetX(0);
		}

		
		/*if (textDims.width > this->GetWidth()) {
			if (mCursorIndex == mLetterPositions.size()) {
				mTextLabel->SetX(this->GetWidth() - textDims.width);
			}
		}
		else {
			mTextLabel->SetX(0);
		}*/
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
				position += mLetterPositions[i];
				minIndex = i;

				if (position + (mLetterPositions[i] * 0.5) > mousePos) {
					break;
				}
			}

			mCursorPosition = position;
			mCursorIndex = minIndex + 1;
		}
	}

	void TextFieldView::ParseFromXML(XMLNode &node)
	{
		FormElement::ParseFromXML(node);

		this->SetText(node.GetAttributeString("text"));
	}
};