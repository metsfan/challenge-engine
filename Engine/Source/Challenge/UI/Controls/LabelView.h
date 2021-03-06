#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/UI/View.h>
#include <Challenge/Font/Font.h>
#include <Challenge/Renderer/Texture.h>
#include <Challenge/Font/GlyphAtlasTexture.h>

namespace challenge
{
	//class Font;
	class Label;

	class LabelView : public View
	{
	public:
		LabelView(Frame frame = Frame());
		virtual ~LabelView();

		void SetText(const std::string &text)
		{
			this->SetText(StringUtil::ToWide(text));
		}

		void SetText(const std::wstring &text);
		const std::wstring& GetText() { return mText; }

		void SetTextColor(Color color) { mTextColor = color; }

		void SetFont(Font *font) { mFont = font; }
		Font* GetFont() { return mFont; }

		virtual void Measure(const Size &parentSize);

		virtual void Update(int deltaMillis);
		virtual void Render(IGraphicsDevice *device, RenderState &state, const Frame &parentFrame);

	protected:
		virtual void ParseFromXML(XMLNode &node);

	private:
		std::wstring mText;
		Font *mFont;
		Color mTextColor;
		//ITexture *mLabelTexture;
		Label *mLabel;
		bool mTextChanged;
		SpriteShape *mLabelSprite;

		static GlyphAtlasTexture *sGlyphTexture;
		//static HLSLProgram *sFontShader;
	};
};