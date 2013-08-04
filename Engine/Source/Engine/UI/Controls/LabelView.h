#pragma once

#include <Engine/Challenge.h>
#include <Engine/UI/View.h>
#include <Engine/Font/Font.h>
#include <Engine/Renderer/Texture.h>

namespace challenge
{
	//class Font;

	class LabelView : public View
	{
	public:
		LabelView();
		LabelView(Frame frame);

		void SetText(std::string text, bool outline);
		std::string GetText() { return mText; }

		void SetTextColor(Color color) { mTextColor = color; }

		void SetFont(Font *font) { mFont = font; }

		virtual void Update(int deltaMillis);
		virtual void Render(IGraphicsDevice *device, RenderState &state);

	private:
		std::string mText;
		Font *mFont;
		Color mTextColor;
		ITexture *mLabelTexture;
		bool mTextChanged;


		//static HLSLProgram *sFontShader;
	};
};