#pragma once

#include <Engine/Challenge.h>
#include <Engine/UI/View.h>
#include <Engine/UI/Controls/LabelView.h>

namespace challenge
{
	class TextFieldView : public View
	{
	public:
		TextFieldView(Frame frame = Frame());
		~TextFieldView();

		void SetText(const std::string &text);
		const std::string& GetText() { return mTextLabel->GetText(); }

		void SetFont(Font *font) { mTextLabel->SetFont(font); }

		virtual void Update(int deltaMillis);
		virtual void Render(IGraphicsDevice *device, RenderState &state, const Frame &parentFrame);

	private:
		LabelView *mTextLabel;
		SpriteShape *mCursorSprite;
		std::vector<int> mLetterPositions;
		bool mCursorActive;
		int mCursorTime;
		int mCursorIndex;
		real mCursorPosition;

		void KeyPressed(const KeyboardEvent &e);
		void JumpCursor(const MouseEvent &e);
	};
};