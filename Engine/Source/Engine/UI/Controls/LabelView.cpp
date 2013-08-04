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
		mTextChanged(false)
	{
		this->SetFont(Font::GetFont(kDefaultFont, kDefaultFontSize));
	}

	LabelView::LabelView(Frame frame) : 
		View(frame),
		mLabelTexture(NULL),
		mFont(NULL),
		mTextChanged(false)
	{
		this->SetFont(Font::GetFont(kDefaultFont, kDefaultFontSize));
	}

	void LabelView::SetText(std::string text, bool outline) 
	{ 
		mText = text; 
		mTextChanged = true;
		/*if(text == "Metsfan") {
			text = "eeeeee";
		}*/
		//text = "Skeletal Archer";
		//text = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcefghijklmnopqrstuvwxyz1234567890!@#$%^&*()_+-=[]{}\|;:'\"/?.>,<`~ ";
		

		
		//CStringBuffer stringBuffer = mFont-(fontString);
		/*if(!mLabelTexture) {
			RendererType rendererType = GameApplication::GetInstance()->GetRendererType();
			if(rendererType == RendererTypeDX11) {
				D3D11_TEXTURE2D_DESC texDesc;
				ZeroMemory(&texDesc, sizeof(D3D11_TEXTURE2D_DESC));
				texDesc.MipLevels = 1;
				texDesc.ArraySize = 1;
				texDesc.Format = DXGI_FORMAT_A8_UNORM;
				texDesc.Usage = D3D11_USAGE_DEFAULT;
				texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
				texDesc.SampleDesc.Count = 1;
				texDesc.SampleDesc.Quality = 0;
				texDesc.CPUAccessFlags = 0;
				texDesc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;
				mLabelTexture = new TextureDX11(texDesc);
			}
		}*/

		//mLabelTexture->Initialize((unsigned char *)stringBuffer.buffer, stringBuffer.texSize.width, stringBuffer.texSize.height);
		/*if(outline) {
			stringBuffer.texSize.width = 54;
		}*/
		//SetSize(Size(stringBuffer.texSize.width, stringBuffer.texSize.height));

		//delete stringBuffer.buffer;
	}

	void LabelView::Update(int deltaMillis)
	{
		View::Update(deltaMillis);
	}

	void LabelView::Render(IGraphicsDevice *device, RenderState &state)
	{
		if(!mLabelTexture) {
			//shader->setUniform("HasText", 1);
			//mLabelTexture->Activate(GL_TEXTURE1);
			//shader->setUniform("FontTexture", 1);
			//glm::vec4 textColorVec = glm::vec4(mTextColor.red, mTextColor.green, mTextColor.blue, mTextColor.alpha);
			//shader->setUniform("Color", textColorVec);
			TEXTURE_DESC desc;
			mLabelTexture = device->CreateTexture2D(desc);
		}

		if(mTextChanged) {
			FONT_UTF8STRING_DESC fontString;
			fontString.Text = mText;
			StringBuffer stringBuffer = mFont->CreateStringBitmap<char>(fontString);

			mLabelTexture->Initialize(stringBuffer.GetBuffer(), stringBuffer.GetSize());

			mTextChanged = false;
		}
	}

	/*void LabelView::OnRender(GLSLProgram *shader)
	{
		View::OnRender(shader);
		mLabelTexture->Activate(GL_TEXTURE0);
		shader->setUniform("FontTexture", 0);
	
		float *texCoords = new float[8];
		texCoords[0] = 0.0f;
		texCoords[1] = 0.0f;

		texCoords[2] = 1.0f;
		texCoords[3] = 0.0f;

		texCoords[4] = 1.0f;
		texCoords[5] = 1.0f;

		texCoords[6] = 0.0f;
		texCoords[7] = 1.0f;

		shader->setAttribData("VertexTexCoord", texCoords, sizeof(float) * 8, 2, 0, GL_FLOAT, GL_DYNAMIC_DRAW, GL_FALSE);

		int hasText = 1;
		shader->setAttribData("HasText", &hasText, sizeof(int), 1, 0, GL_INT, GL_DYNAMIC_DRAW, GL_FALSE);

		delete texCoords;
	}*/
};
