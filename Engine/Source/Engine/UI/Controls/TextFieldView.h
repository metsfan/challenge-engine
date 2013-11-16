#pragma once

#include <Engine/Challenge.h>
#include <Engine/UI/Controls/FormElement.h>
#include <Engine/UI/Controls/LabelView.h>
#include <Engine/Util/Timer.h>

namespace challenge
{
	class TextFieldView : public FormElement
	{
	public:
		TextFieldView(Frame frame = Frame());
		~TextFieldView();

		void SetText(const std::string &text);
		const std::string& GetText() { return mTextLabel->GetText(); }

		void SetFont(Font *font) { mTextLabel->SetFont(font); }

		virtual void Update(int deltaMillis);
		virtual void Render(IGraphicsDevice *device, RenderState &state, const Frame &parentFrame);

		void SetValue(const std::string &value) { this->SetText(value); }
		std::string GetValue() { return mTextLabel->GetText(); }

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