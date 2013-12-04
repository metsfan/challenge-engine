#include <Engine/Challenge.h>
#include <Engine/UI/Controls/Model3DView.h>
#include <Engine/Renderer/Shape/RenderableSpriteShape.h>

namespace challenge
{
	Model3DView::Model3DView(Frame frame) :
		View(frame),
		mModel(NULL),
		mTargetSprite(NULL)
	{
		glm::mat4 projection = glm::perspective(45.0f, frame.size.width / frame.size.height, 0.1f, 100.0f);
		mCamera = new Camera(projection, Size(frame.size.width, frame.size.height));
	}

	Model3DView::~Model3DView()
	{
		if (mTargetSprite) {
			delete mTargetSprite;
		}

		delete mCamera;
	}

	void Model3DView::SetModel(Model *model)
	{
		mModel = model;
		mModel->SetActiveAnimation("idle");
	}

	void Model3DView::Render(IGraphicsDevice *device, RenderState &state, const Frame &parentFrame)
	{
		if (!mTargetSprite) {
			int width = this->GetWidth();
			int height = this->GetHeight();
			TByteArray data(width * height * 4);

			TEXTURE_DESC texDesc;
			ITexture *texture = device->CreateTexture2D(texDesc);
			texture->Initialize(&data[0], Size(width, height));

			RENDER_TARGET_DESC desc;
			desc.Width = width;
			desc.Height = height;
			desc.ColorTexture = texture;
			desc.DepthFormat = DepthStencilFormatD24S8;

			mTargetSprite = new RenderableSpriteShape(device, desc);
			mTargetSprite->SetSize(width, height);
			mTargetSprite->SetPosition(this->GetX(), this->GetY());
		}

		View::Render(device, state, parentFrame);

		RenderState modelState;

		mModel->SetNextFrame(16);

		mCamera->Update();
		modelState.SetProjection(mCamera->GetProjectionMatrix());
		modelState.PushTransform(mCamera->GetViewMatrix());

		mTargetSprite->EnableRenderTarget();
		mTargetSprite->ClearRenderTarget();

		device->EnableState(DepthTest);
		device->PushScissorRect(0, 0, this->GetWindow()->GetWidth(), this->GetWindow()->GetHeight());

		mModel->Render(device, modelState);

		device->DisableState(DepthTest);
		device->PopScissorRect();
		mTargetSprite->DisableRenderTarget();

		mTargetSprite->Draw(device, state);
	}
}