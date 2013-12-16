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
			std::stringstream ss;
			ss << val;
			this->SetText(ss.str());
		}

		void SetText(const std::string &text);
		const std::string& GetText() { return mTextLabel->GetText(); }

		void SetFont(Font *font) { mTextLabel->SetFont(font); }

		virtual void Update(int deltaMillis);
		virtual void Render(IGraphicsDevice *device, RenderState &state, const Frame &parentFrame);

		void SetValue(const std::string &value) { this->SetText(value); }
		std::string GetValue() { return mTextLabel->GetText(); }

		void ResetCursor();

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

		int mKeyPressTime;
		int mKeyRepeatTime;
		bool mKeyPressed;

		void KeyPressed(const KeyboardEvent &e);
		void JumpCursor(const MouseEvent &e);
	};
};