#include <Engine/Challenge.h>
#include <Engine/Font/UnicodeRanges.h>
#include "TextFieldView.h"

namespace challenge
{
	static const int kCursorDuration = 500;
	static const char kBackspaceKey = 8;

	TextFieldView::TextFieldView(Frame frame) :
		FormElement(frame),
		mTextLabel(new LabelView(Frame(0, 0, frame.size.width, frame.size.height))),
		mCursor(new View(Frame(0, 0, 1, frame.size.height - 2))),
		mCursorActive(false),
		mCursorTime(0),
		mCursorPosition(1),
		mCursorIndex(0)
	{
		this->SetBackgroundColor(Color(255, 255, 255, 255));

		this->AddKeyDownDelegate([this](View *sender, const KeyboardEvent &e) {
			this->KeyPressed(e);
		});

		this->AddKeyPressDelegate([this](View *sender, const KeyboardEvent &e) {
			// Do nothing, just capture the event so others can't.
		});

		this->AddKeyUpDelegate([this](View *sender, const KeyboardEvent &e) {
			// Do nothing, just capture the event so others can't.
		});

		this->AddMouseDownDelegate([this](View *sender, const MouseEvent &e) {
			this->JumpCursor(e);
		});

		this->AddInternalSubview(mTextLabel);

		mCursor->SetBackgroundColor(Color(0, 0, 0, 255));
		mTextLabel->AddSubview(mCursor);

		mLetterPositions.push_back(mCursorPosition);
		
		this->ClipSubviews(true);
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
		mCursor->SetX(50);
		if(this->IsFocused() || true) {
			mCursorTime += 16;
			if(mCursorTime > kCursorDuration) {
				mCursorActive = !mCursorActive;
				mCursorTime = 0;
			}

			mCursor->SetVisible(mCursorActive);
			//mCursor->SetX(mCursorPosition-2);
		} else {
			mCursorTime = 0;
			mCursor->SetVisible(false);
		}

		Size textDims = mTextLabel->GetFont()->GetStringDimensions(mTextLabel->GetText());
		if(textDims.width > this->GetWidth()) {
			if(mCursorIndex == mLetterPositions.size() - 1) {
				mTextLabel->SetX(this->GetWidth() - textDims.width);
			}
		} else {
			mTextLabel->SetX(0);
		}
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
		} else if(ASCII_RANGE.Contains(c)) {
			text.insert(text.begin() + mCursorIndex, c);

			Size letterSize = mTextLabel->GetFont()->GetStringDimensions(std::string(1, c));
			mCursorPosition += letterSize.width;
			
			mCursorIndex++;
			mLetterPositions.insert(mLetterPositions.begin() + mCursorIndex, letterSize.width);
		}

		mTextLabel->SetText(text);
	}

	void TextFieldView::JumpCursor(const MouseEvent &e)
	{
		if(mLetterPositions.size() > 0) {
			int minDif = kInfinity;
			int minIndex = 0;

			int position = 0;
			for(int i = 0; i < mLetterPositions.size(); i++) {
				int positionInLabel = e.position.x - mTextLabel->GetX();

				if(position + mLetterPositions[i] > positionInLabel) {
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