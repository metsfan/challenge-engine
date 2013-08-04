#pragma once

#include <Engine/Challenge.h>
#include <Engine/UI/View.h>
#include <Engine/Font/Font.h>
#include <Engine/Renderer/Texture.h>
namespace challenge
{
	class LabelView : public View
	{
	public:
		LabelView(void);
		LabelView(Frame frame);

		void SetText(std::string text, bool outline);
		std::string GetText() { return mText; }

		void SetTextColor(Color color) { mTextColor = color; }

		void SetFont(std::string fontName, int size);

		virtual void Render(UIManager *manager, Point origin);

	private:
		std::string mText;
		Font *mFont;
		Color mTextColor;
		ITexture *mLabelTexture;


		//static HLSLProgram *sFontShader;
	};
};