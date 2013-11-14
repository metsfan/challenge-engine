#include <Engine/Challenge.h>
#include <Engine/UI/ViewManager.h>
#include <Engine/Font/FontEngine.h>
#include <Engine/Font/Font.h>
#include <Engine/GameApplication.h>
#include <Engine/Renderer/Texture/Texture2DDX11.h>
#include <Engine/UI/Controls/LabelView.h>

namespace challenge
{
	static const std::string kDefaultFont = "arial";
	static const int kDefaultFontSize = 13;

	LabelView::LabelView(Frame frame) : 
		View(frame),
		mLabelTexture(NULL),
		mFont(NULL),
		mTextChanged(false),
		mLabelSprite(NULL)
	{
		this->SetFont(Font::GetFont(kDefaultFont, kDefaultFontSize));
	}

	void LabelView::SetText(const std::string &text) 
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
			if(mText.length() > 0) {
				FONT_UTF8STRING_DESC fontString;
				fontString.Text = mText;
				StringBuffer stringBuffer = mFont->CreateStringBitmap<char>(fontString);

				mLabelTexture->Initialize(stringBuffer.GetBuffer(), stringBuffer.GetSize());
				//mLabelSprite->SetSize(stringBuffer.GetSize().width, stringBuffer.GetSize().height);
				Size stringDims = mFont->GetStringDimensions(mText);
				/*if(frame.size.width < stringDims.width) {
					real dif = stringDims.width - frame.size.width;
					real texX = dif / stringBuffer.GetSize().width;

					mLabelSprite->SetTextureFrame(texX, 0, 1 - texX, 1);
					mLabelSprite->SetSize(stringBuffer.GetSize().width * (1 - texX), stringBuffer.GetSize().height);
				} else*/ {
					mLabelSprite->SetTextureFrame(0, 0, 1, 1);
					mLabelSprite->SetSize(stringBuffer.GetSize().width, stringBuffer.GetSize().height);
				}
				
				
			}
			
			mTextChanged = false;
		}

		if(mText.length() > 0) {
			mLabelSprite->SetTextureFrame(this->GetTextureFrame());
			mLabelSprite->SetPosition(frame.origin.x + parentFrame.origin.x,
									frame.origin.y + parentFrame.origin.y - 5);
			
			mLabelSprite->Draw(device, state);
		}
	}
	
	void LabelView::ParseFromXML(XMLNode &node)
	{
		View::ParseFromXML(node);

		this->SetText(node.GetAttributeString("text"));
		this->SetTextColor(Color::FromHexString(node.GetAttributeString("text_color")));
	}
};
