#include <Engine/Challenge.h>
#include <Engine/Font/UnicodeRanges.h>
#include "TextFieldView.h"

namespace challenge
{
	static const int kCursorDuration = 500;
	static const char kBackspaceKey = 8;

	TextFieldView::TextFieldView(Frame frame) :
		View(frame),
		mTextLabel(new LabelView(frame)),
		mCursorSprite(NULL),
		mCursorActive(false),
		mCursorTime(0),
		mCursorPosition(1),
		mCursorIndex(0)
	{
		this->SetBackgroundColor(glm::vec4(255));

		this->AddKeyDownDelegate([this](View *sender, const KeyboardEvent &e) {
			this->KeyPressed(e);
		});

		this->AddMouseDownDelegate([this](View *sender, const MouseEvent &e) {
			this->JumpCursor(e);
		});

		mLetterPositions.push_back(mCursorPosition);
	}

	TextFieldView::~TextFieldView()
	{
	}

	void TextFieldView::Update(int deltaMillis)
	{
		mCursorTime += 16;
		if(mCursorTime > kCursorDuration) {
			mCursorActive = !mCursorActive;
			mCursorTime = 0;
		}
	}

	void TextFieldView::Render(IGraphicsDevice *device, RenderState &state, const Frame &parentFrame)
	{
		View::Render(device, state, parentFrame);

		const Frame &frame = this->GetFrame();

		if(!mCursorSprite) {
			mCursorSprite = new SpriteShape(device);
			mCursorSprite->SetBackgroundColor(glm::vec4(0, 0, 0, 255));
			mCursorSprite->SetSize(1, frame.size.height - 2);
		}

		if(mCursorActive) {
			mCursorSprite->SetPosition(
				mCursorPosition + parentFrame.origin.x + frame.origin.x, 
				1 + parentFrame.origin.y + frame.origin.y
			);
			mCursorSprite->Draw(device, state);
		}

		mTextLabel->Render(device, state, parentFrame);
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
				Size textSize = mTextLabel->GetFont()->GetStringDimensions(text);
				if(textSize.width <= frame.size.width) {
					mCursorPosition = mLetterPositions[mCursorIndex];
				} else {
					mCursorPosition = frame.size.width - 1;
				}
				
				mLetterPositions.erase(mLetterPositions.begin() + mCursorIndex);
				text.erase(text.begin() + mCursorIndex);
			}
		} else if(ASCII_RANGE.Contains(c)) {
			text.insert(text.begin() + mCursorIndex, c);

			Size letterSize = mTextLabel->GetFont()->GetStringDimensions(std::string(1, c));
			Size textSize = mTextLabel->GetFont()->GetStringDimensions(text);
			if(textSize.width <= frame.size.width) {
				mCursorPosition += letterSize.width;
			} else {
				mCursorPosition = frame.size.width - 1;
			}
			
			mCursorIndex++;
			mLetterPositions.insert(mLetterPositions.begin() + mCursorIndex, mCursorPosition);
		}

		mTextLabel->SetText(text);
	}

	void TextFieldView::JumpCursor(const MouseEvent &e)
	{
		if(mLetterPositions.size() > 0) {
			int minDif = kInfinity;
			int minIndex = 0;

			for(int i = 0; i < mLetterPositions.size(); i++) {
				if(mLetterPositions[i] > e.position.x) {
					break;
				}
				minIndex = i;
			}

			mCursorPosition = mLetterPositions[minIndex];
			mCursorIndex = minIndex;
		}
		
	}

};