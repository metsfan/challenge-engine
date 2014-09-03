#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/UI/Controls/FormElement.h>
#include <Challenge/UI/Controls/LabelView.h>
#include <Challenge/Util/Timer.h>

namespace challenge
{
	class TextFieldView : public FormElement
	{
	public:
		TextFieldView(Frame frame = Frame());
		virtual ~TextFieldView();

		template <typename T>
		void SetText(const T &val)
		{
			std::wstringstream ss;
			ss << val;
			this->SetText(ss.str());
		}

		void SetText(const std::string &text)
		{
			this->SetText(StringUtil::ToWide(text));
		}

		void SetText(const std::wstring &text);

		template <typename T>
		void SetPlaceholder(const T &val)
		{
			std::wstringstream ss;
			ss << val;
			this->SetPlaceholder(ss.str());
		}

		void SetPlaceholder(const std::string &text)
		{
			this->SetPlaceholder(StringUtil::ToWide(text));
		}

		void SetPlaceholder(const std::wstring &text)
		{
			mPlaceholder = text;
		}

		const std::string& GetText() { return StringUtil::ToNarrow(mText); }

		void SetFont(Font *font);

		virtual void Update(int deltaMillis);
		virtual void Render(IGraphicsDevice *device, RenderState &state, const Frame &parentFrame);

		void SetValue(const std::string &value) { this->SetText(value); }
		std::string GetValue() { return StringUtil::ToNarrow(mText); }

		void ResetCursor();

		bool IsSecure() { return mSecure; }
		void SetSecure(bool secure) { mSecure = secure; }

		virtual void Measure(const Size &parentSize);

	protected:
		virtual void ParseFromXML(XMLNode &node);

	private:
		LabelView *mTextLabel;
		View *mCursor;
		std::vector<int> mLetterPositions;
		bool mCursorActive;
		int mCursorTime;
		int mCursorIndex;
		real mCursorPosition;
		bool mSecure;
		std::wstring mText;
		std::wstring mSecureString;
		Size mSecureCharSize;
		std::wstring mPlaceholder;


		int mKeyPressTime;
		int mKeyRepeatTime;
		bool mKeyPressed;

		void KeyPressed(const KeyboardEvent &e);
		void JumpCursor(const MouseEvent &e);
	};
};