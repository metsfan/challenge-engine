#include <Challenge/Challenge.h>
#include <Challenge/Font/UnicodeRanges.h>
#include <Challenge/Font/TextUtil.h>
#include <Challenge/Font/Glyph.h>
#include <Challenge/Font/Font.h>
#include <Challenge/Font/FontManager.h>
#include "TextFieldView.h"

namespace challenge
{
	static const int kCursorDuration = 500;
	static const int kKeyPressDuration = 500;
	static const int kKeyRepeatInterval = 50;
	static const char kBackspaceKey = 8;

	static const int kLetterPadding = 1;

	static const wchar_t kSecureChar = L'*';

	TextFieldView::TextFieldView(Frame frame) :
		FormElement(frame),
		mTextLabel(new LabelView(Frame(0, 0, frame.size.width, frame.size.height))),
		mCursor(new View(Frame(0, 1, 1, frame.size.height - 2))),
		mCursorActive(false),
		mCursorTime(0),
		mCursorPosition(2),
		mCursorIndex(0),
		mKeyPressTime(0),
		mKeyPressed(false),
		mSecure(false)
	{
		this->SetBackgroundColor(Color(255, 255, 255, 255));

		this->SetFont(FontManager::GetDefaultFont());

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
		this->AddSubview(mCursor);
		mTextLabel->SetBackgroundColor(Color::Clear());

		//mLetterPositions.push_back(mCursorPosition);
		
		this->ClipSubviews(true);

		this->SetBorderColor(Color::Black());
		this->SetBorderWidth(1);
	}

	TextFieldView::~TextFieldView()
	{
	}

	void TextFieldView::SetFont(Font *font)
	{
		mTextLabel->SetFont(font);

		std::wstring testStr;
		testStr.push_back(kSecureChar);
		mSecureCharSize = TextUtil::SizeOfText(testStr, font);
	}

	void TextFieldView::SetText(const std::wstring &text)
	{
		mText = text;

		if (mSecure) {
			std::wstring secureString;
			for (int i = 0; i < mText.length(); i++) {
				secureString.push_back(kSecureChar);
			}

			mTextLabel->SetText(secureString);
		}
		else {
			mTextLabel->SetText(text);
		}
		
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
			mCursor->SetX(mCursorPosition + mTextLabel->GetX());
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
		unsigned char c = e.virtualKeyCode;
		if(e.shiftDown) {
			c = toupper(c);
		}
		else {
			c = tolower(c);
		}

		std::wstring text = mText;

		int newOffset = 0;

		if(c == kBackspaceKey) {
			if(mCursorIndex > 0) {
				int newPosition = 0;
				/*for(int i = 0; i < mCursorIndex; i++) {
					newPosition += mLetterPositions[i];
				}*/
				mCursorIndex--;

				if (mSecure) {
					newOffset = -mSecureCharSize.width;
				}
				else {
					newOffset = -mLetterPositions[mCursorIndex];
				}

				mLetterPositions.erase(mLetterPositions.begin() + mCursorIndex);
				text.erase(text.begin() + mCursorIndex);
				
			}
		}
		else if (c < 127 && c >= 32) {
			text.insert(text.begin() + mCursorIndex, c);

			if (mSecure) {
				newOffset = mSecureCharSize.width;
			}
			else {
				Glyph *glyph = mTextLabel->GetFont()->GetGlyph(c);
				newOffset = glyph->GetAdvance().x;
			}
			
			mLetterPositions.insert(mLetterPositions.begin() + mCursorIndex, newOffset);
			
			mCursorIndex++;
		}

		mCursorPosition += newOffset;
		this->SetText(text);

		Size textDims;
		
		if (mSecure) {
			textDims = mSecureCharSize;
		}
		else {
			textDims = TextUtil::SizeOfText(mTextLabel->GetText(), mTextLabel->GetFont());
		}

		if (textDims.width > this->GetWidth() && 
			((mCursorPosition + mTextLabel->GetX()) >= this->GetWidth() ||
			(mCursorPosition + mTextLabel->GetX()) < 0)) {
			mTextLabel->SetX(mTextLabel->GetX() - (50 * glm::sign(newOffset)));
			//mTextLabel->SetWidth(mTextLabel->GetWidth() + 50);
		}
		else if (textDims.width < this->GetWidth()) {
			mTextLabel->SetX(0);
		}

		mTextLabel->SetWidth(this->GetWidth() - mTextLabel->GetX() + 10);

		Logger::Log(LogDebug, "Cursor: %f, Label: %f", mCursorPosition, mTextLabel->GetX());

		
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

		bool secure = node.GetAttributeString("secure") == "true";
		this->SetSecure(secure);
	}
};