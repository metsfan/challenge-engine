#include <Engine/Challenge.h>
#include <Engine/Renderer/Shape/SpriteShape.h>
#include <Engine/Renderer/Effect.h>

namespace challenge
{
	static IVertexBuffer *sSpriteVertexBuffer = NULL;

	SpriteShape::SpriteShape(IGraphicsDevice *device) :
		Shape(device, "sprite"),
		mBackgroundImage(NULL)
	{
		if(!sSpriteVertexBuffer) {
			// Create sprite vertex buffer, which all sprites will use
			SpriteVertex verts[4] = {
				0.0, 0.0, 0.0, 0.0,
				0.0, 1.0, 0.0, 1.0,
				1.0, 0.0, 0.0, 1.0,
				1.0, 1.0, 1.0, 1.0,
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
		mBackgroundColor = color;
	}

	void SpriteShape::SetBackgroundImage(Image *backgroundImage)
	{
		TEXTURE_DESC desc;
		mBackgroundImage = this->GetDevice()->CreateTexture2D(desc);
		if(!mBackgroundImage->Initialize(backgroundImage)) {
			throw "Failed to load texture";
		}
	}

	void SpriteShape::Draw(IGraphicsDevice *device, RenderState &state)
	{
		IGraphicsContext *context = device->GetContext();
		
		Effect *effect = context->GetEffect("Sprite");
		if(mBackgroundImage) {
			effect->SetActiveTechnique("SpriteTexture");
		} else {
			effect->SetActiveTechnique("SpriteColor");
		}

		glm::mat4 wvp = state.GetWorldViewProjection();
		ShaderDataMatrix4 wvpData(&wvp, 1);
		state.SetShaderData("WORLDVIEWPROJ_MATRIX", &wvpData);

		ShaderDataVector4 colorData(&mBackgroundColor, 1);
		state.SetShaderData("BACKGROUND_COLOR", &colorData);

		if(mBackgroundImage) {
			ShaderDataTexture bgImageData(mBackgroundImage);
			state.SetShaderData("BACKGROUND_IMAGE", &bgImageData);
		}

		if(sSpriteVertexBuffer) {
			Technique *technique = effect->GetActiveTechnique();
			while(technique->HasNextPass()) {
				sSpriteVertexBuffer->Activate();
				technique->ProcessNextPass(device, state);
				device->Draw(PrimitiveTypeTriangleStrip, 4, 0);
			}
		}
	}
};