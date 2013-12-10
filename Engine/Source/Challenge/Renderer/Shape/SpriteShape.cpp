#include <Challenge/Challenge.h>
#include <Challenge/Renderer/Shape/SpriteShape.h>
#include <Challenge/Renderer/Effect.h>

namespace challenge
{
	static IVertexBuffer *sSpriteVertexBuffer = NULL;

	SpriteShape::SpriteShape(IGraphicsDevice *device, const std::string &effect, ITexture *texture) :
		Shape(device, effect),
		mBackgroundImage(texture),
		mHasBackgroundImage(texture != NULL),
		mTexFrame(0, 0, 1, 1),
		mBorderWidth(0)
	{
		if(!sSpriteVertexBuffer) {
			// Create sprite vertex buffer, which all sprites will use
			SpriteVertex verts[4] = {
				0.0, 0.0,
				1.0, 0.0,
				0.0, 1.0,
				1.0, 1.0
			};

			VERTEX_BUFFER_DESC desc;
			desc.Stride = sizeof(SpriteVertex);
			desc.Usage = VertexBufferUsageStatic;
			desc.CPUAccess = 0;

			sSpriteVertexBuffer = device->CreateVertexBuffer(desc);
			sSpriteVertexBuffer->SetData(verts, sizeof(SpriteVertex) * 4);
		}
	}

	SpriteShape::~SpriteShape()
	{
		delete mBackgroundImage;
	}

	void SpriteShape::SetBackgroundColor(const glm::vec4 &color)
	{
		mBackgroundColor = glm::vec4(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);
	}

	void SpriteShape::SetBackgroundImage(Image *backgroundImage)
	{
		if(backgroundImage) {
			TEXTURE_DESC desc;
			mBackgroundImage = this->GetDevice()->CreateTexture2D(desc);
			if(!mBackgroundImage->Initialize(backgroundImage)) {
				throw "Failed to load texture";
			}
			mHasBackgroundImage = true;
		} else {
			mHasBackgroundImage = false;
		}
	}

	void SpriteShape::Draw(IGraphicsDevice *device, RenderState &state)
	{
		IGraphicsContext *context = device->GetContext();
		
		Effect *effect = context->GetEffect("Sprite");
		if(mHasBackgroundImage) {
			effect->SetActiveTechnique("SpriteTexture");
		} else {
			effect->SetActiveTechnique("SpriteColor");
		}

		glm::mat4 wvp = state.GetWorldViewProjection();
		ShaderDataMatrix4 wvpData(&wvp, 1);
		state.SetShaderData("WORLDVIEWPROJ_MATRIX", &wvpData);

		ShaderDataVector4 frameData(&mFrame, 1);
		state.SetShaderData("FRAME", &frameData);

		ShaderDataVector4 texFrameData(&mTexFrame, 1);
		state.SetShaderData("TEXTURE_FRAME", &texFrameData);

		ShaderDataVector4 colorData(&mBackgroundColor, 1);
		state.SetShaderData("BACKGROUND_COLOR", &colorData);

		ShaderDataTexture bgImageData(mBackgroundImage);
		if(mBackgroundImage) {
			state.SetShaderData("BACKGROUND_IMAGE", &bgImageData);
		}

		ShaderDataFloat borderWidthData(&mBorderWidth, 1);
		state.SetShaderData("BORDER_WIDTH", &borderWidthData);

		ShaderDataVector4 borderColorData(&mBorderColor, 1);
		state.SetShaderData("BORDER_COLOR", &borderColorData);

		if(sSpriteVertexBuffer) {
			Technique *technique = effect->GetActiveTechnique();
			technique->Begin();
			while(technique->HasNextPass()) {
				sSpriteVertexBuffer->Activate();
				technique->ProcessNextPass(device, state);
				device->Draw(PrimitiveTypeTriangleStrip, 4, 0);
			}
		}
	}
};