#include <Challenge/Challenge.h>
#include <Challenge/Renderer/Shape/SpriteShape.h>
#include <Challenge/Renderer/Effect.h>

namespace challenge
{
	static IVertexBuffer *sSpriteVertexBuffer = NULL;

	SpriteShape::SpriteShape(IGraphicsDevice *device, const std::string &effect, ITexture *texture) :
		Shape(device, effect),
		mBackgroundColor(0, 0, 0, 1),
		mBackgroundImage(texture),
		mHasBackgroundImage(texture != NULL),
		mTexFrame(0, 0, 1, 1),
		mBorderWidth(0)
	{
		if(!sSpriteVertexBuffer) {
			// Create sprite vertex buffer, which all sprites will use
			SpriteVertex verts[4] = {
				0.0, 0.0,
				0.0, 1.0,
				1.0, 0.0,
				1.0, 1.0
			};

			VERTEX_BUFFER_DESC desc;
			desc.Stride = sizeof(SpriteVertex);
			desc.Usage = VertexBufferUsageStatic;
			desc.CPUAccess = 0;

			sSpriteVertexBuffer = device->CreateVertexBuffer(desc);
			sSpriteVertexBuffer->SetData(verts, sizeof(SpriteVertex) * 4, sizeof(SpriteVertex));
		}

		IGraphicsContext *context = device->GetContext();
		mWVPIndex = context->GetGlobalIndex("WORLDVIEWPROJ_MATRIX");
		mFrameIndex = context->GetGlobalIndex("FRAME");
		mTextureFrameIndex = context->GetGlobalIndex("TEXTURE_FRAME");
		mBackgroundColorIndex = context->GetGlobalIndex("BACKGROUND_COLOR");
		mBackgroundImageIndex = context->GetGlobalIndex("BACKGROUND_IMAGE");
		mBorderWidthIndex = context->GetGlobalIndex("BORDER_WIDTH");
		mBorderColorIndex = context->GetGlobalIndex("BORDER_COLOR");
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

			mTexFrame = glm::vec4(0, 0, 1, 1);
			mFrame.z = backgroundImage->GetSize().width;
			mFrame.w = backgroundImage->GetSize().height;
		} else {
			mHasBackgroundImage = false;
		}
	}

	void SpriteShape::SetBackgroundImage(ImageAtlas *atlas, const std::string &key)
	{
		std::string texKey = std::to_string(reinterpret_cast<uint64_t>(atlas));

		IGraphicsContext *context = this->GetDevice()->GetContext();
		mBackgroundImage = context->GetSharedTexture(texKey);
		if (!mBackgroundImage) {
			this->SetBackgroundImage(atlas->GetImage().get());
			context->PutSharedTexture(texKey, mBackgroundImage);
		}

		mHasBackgroundImage = true;

		const Frame &texFrame = atlas->GetTexCoords(key);
		mTexFrame.x = texFrame.origin.x;
		mTexFrame.y = texFrame.origin.y;
		mTexFrame.z = texFrame.size.width;
		mTexFrame.w = texFrame.size.height;
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

		state.SetShaderData(mWVPIndex, &wvp);
		state.SetShaderData(mFrameIndex, &mFrame);
		state.SetShaderData(mTextureFrameIndex, &mTexFrame);
		state.SetShaderData(mBackgroundColorIndex, &mBackgroundColor);

		if(mBackgroundImage) {
			state.SetShaderData(mBackgroundImageIndex, mBackgroundImage);
		}

		state.SetShaderData(mBorderWidthIndex, &mBorderWidth);
		state.SetShaderData(mBorderColorIndex, &mBorderColor);

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