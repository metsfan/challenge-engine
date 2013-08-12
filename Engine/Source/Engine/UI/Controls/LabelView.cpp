#include <Engine/Challenge.h>
#include <Engine/UI/UIManager.h>
#include <Engine/Font/FontEngine.h>
#include <Engine/Font/Font.h>
#include <Engine/GameApplication.h>
#include <Engine/Renderer/Texture/Texture2DDX11.h>
#include <Engine/UI/Controls/LabelView.h>

namespace challenge
{
	static const std::string kDefaultFont = "arial";
	static const int kDefaultFontSize = 15;

	LabelView::LabelView() : 
		View(),
		mLabelTexture(NULL),
		mFont(NULL),
		mTextChanged(false),
		mLabelSprite(NULL)
	{
		this->SetFont(Font::GetFont(kDefaultFont, kDefaultFontSize));
	}

	LabelView::LabelView(Frame frame) : 
		View(frame),
		mLabelTexture(NULL),
		mFont(NULL),
		mTextChanged(false),
		mLabelSprite(NULL)
	{
		this->SetFont(Font::GetFont(kDefaultFont, kDefaultFontSize));
	}

	void LabelView::SetText(std::string text, bool outline) 
	{ 
		mText = text; 
		mTextChanged = true;
	}

	void LabelView::Update(int deltaMillis)
	{
		View::Update(deltaMillis);
	}

	void LabelView::Render(IGraphicsDevice *device, RenderState &state, const Frame &parentFrame)
	{
		//this->SetBackgroundColor(glm::vec4(0, 255, 255, 255));
		//this->SetSize(50, 50);
		//this->SetPosition(0, 0);
		View::Render(device, state, parentFrame);

		const Frame &frame = this->GetFrame();

		if(!mLabelTexture) {
			TEXTURE_DESC desc;
			mLabelTexture = device->CreateTexture2D(desc);
		}

		if(!mLabelSprite) {
			mLabelSprite = new SpriteShape(device, mLabelTexture);
		}

		if(mTextChanged) {
			FONT_UTF8STRING_DESC fontString;
			fontString.Text = mText;
			StringBuffer stringBuffer = mFont->CreateStringBitmap<char>(fontString);

			mLabelTexture->Initialize(stringBuffer.GetBuffer(), stringBuffer.GetSize());

			mTextChanged = false;

			mLabelSprite->SetSize(stringBuffer.GetSize().width, stringBuffer.GetSize().height);
		}

		mLabelSprite->SetPosition(frame.origin.x + parentFrame.origin.x,
									frame.origin.y + parentFrame.origin.y);
		mLabelSprite->Draw(device, state);
	}
};
