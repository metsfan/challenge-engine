#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/UI/View.h>
#include <Challenge/Font/Font.h>
#include <Challenge/Renderer/Texture.h>

namespace challenge
{
	//class Font;

	class LabelView : public View
	{
	public:
		LabelView(Frame frame = Frame());
		virtual ~LabelView();

		void SetText(const std::string &text);
		const std::string& GetText() { return mText; }

		void SetTextColor(Color color) { mTextColor = color; }

		void SetFont(Font *font) { mFont = font; }
		Font* GetFont() { return mFont; }

		virtual void Update(int deltaMillis);
		virtual void Render(IGraphicsDevice *device, RenderState &state, const Frame &parentFrame);

	protected:
		virtual void ParseFromXML(XMLNode &node);

	private:
		std::string mText;
		Font *mFont;
		Color mTextColor;
		ITexture *mLabelTexture;
		bool mTextChanged;
		SpriteShape *mLabelSprite;


		//static HLSLProgram *sFontShader;
	};
};