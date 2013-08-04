#include <Engine/Challenge.h>
#include <Engine/GameApplication.h>
#include <Engine/Renderer/VertexBuffer/VertexBufferDX11.h>
#include <d3dx9math.h>
#include "UIManager.h"
using namespace challenge;

UIManager::UIManager()
{
	//mShader = NULL;
}
UIManager::~UIManager()
{
}

void UIManager::AddControl(View *control)
{
	mControlCount++;
}

void UIManager::AddRootControl(View *control)
{
	mRootControls.push_back(control);
}

void UIManager::Update(int deltaMillis)
{
	//if(mShader == NULL) {
		mProjectionMatrix = glm::ortho(0.0f, 1280.0f, 1024.0f, 0.0f, -10.0f, 10.0f);

		/*D3DXMATRIX proj;
		D3DXMatrixOrthoRH(&proj, 1280.0f, 1024.0f, 0.1, 1000.0f);
		//D3DXMatrixOrthoOffCenterRH (&proj,  0.0, 1280.0f, 0.0f, 1024.0f,-1.0f, 1.0);

		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 4; j++) {
				mProjectionMatrix[i][j] = proj.m[i][j];
			}
		}*/

		mControlCount = 0;
		//mImageAtlas = new CTextureAtlas(512, 512);
		//mTextAtlas = new CTextureAtlas(512, 512);

		ControlVertex controlCoords[4] = {
			{ 1.0f, 1.0f, 1.0f, 1.0f, 0.0f },
			{ 1.0f, 0.0f, 1.0f, 1.0f, 1.0f },
			{ 0.0f, 1.0f, 1.0f, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0f, 0.0f, 1.0f },
		};

		//mShader = new HLSLProgram();
		//mShader->AddShader("ControlVertex", HLSLShaderTypeVertex);
		//mShader->AddShader("ControlPixel", HLSLShaderTypePixel);
		//mShader->SetInputLayout(controlVertexDesc, 2);

		mVertexBuffer = GameApplication::GetInstance()->CreateVertexBuffer(controlCoords, sizeof(ControlVertex) * 4);
	//}

	int numControls = mRootControls.size();
	
	int p = 0, c = 0;

	//UIControlData *data = new UIControlData(mControlCount);
	
	for(int i = 0; i < numControls; i++) {
		View *next = mRootControls[i];
		next->UpdateBase(deltaMillis);
	}

	/*mShader->use();
	mShader->setAttribData("VertexPosition", data->positionBuffer, sizeof(float) * mControlCount * 12, 3, 0, GL_FLOAT, GL_DYNAMIC_DRAW, GL_FALSE);
	mShader->setAttribData("VertexColor", data->colorBuffer, sizeof(float) * mControlCount * 16, 4, 0, GL_FLOAT, GL_DYNAMIC_DRAW, GL_FALSE);
	mShader->setAttribData("VertexTexCoord", data->texCoordBuffer, sizeof(float) * mControlCount * 8, 2, 0, GL_FLOAT, GL_DYNAMIC_DRAW, GL_FALSE);
	mShader->setAttribData("VertexHasText", data->hasTextBuffer, sizeof(int) * mControlCount * 4, 1, 0, GL_INT, GL_DYNAMIC_DRAW, GL_FALSE);
	mShader->setAttribData("VertexHasTexture", data->hasTextureBuffer, sizeof(int) * mControlCount * 4, 1, 0, GL_INT, GL_DYNAMIC_DRAW, GL_FALSE);

	mImageAtlas->Activate(GL_TEXTURE0);
	mShader->setUniform("BackgroundImage", 0);

	delete data;*/
}

void UIManager::Render()
{
	//mShader->use();
	//mShader->UseProgram();
	mVertexBuffer->Activate();

	int numControls = mRootControls.size();
	
	//Renderer *renderer = GameApplication::GetInstance()->GetWindow()->GetRenderer();

	//renderer->DisableState(RendererStateDepthTest);
	//renderer->EnableState(RendererStateAlphaBlending);

	for(int i = 0; i < numControls; i++) {
		View *next = mRootControls[i];
		next->RenderBase(this, Point(0, 0));
	}

	//renderer->EnableState(RendererStateDepthTest);
	//renderer->DisableState(RendererStateAlphaBlending);
}

void UIManager::AddImageToAtlas(Image *image)
{
	//mImageAtlas->AddBitmap(image->GetBits(), image->GetWidth(), image->GetHeight(), image->GetFilename());
}

/*TextureAtlasEntry UIManager::GetImageForKey(std::string key)
{
	return mImageAtlas->GetEntryForKey(key);
}*/

UIManager* UIManager::GetDefaultManager() {
	GameApplication *gApp = GameApplication::GetInstance();
	return gApp->GetUIManager();
}

void UIManager::ProcessKeyboardEvent(const KeyboardEvent &e)
{
	for(int i = 0; i < mRootControls.size(); i++) {
		View *next = mRootControls[i];
		next->OnKeyboardEvent(e);
	}
}

void UIManager::ProcessMouseEvent(const MouseEvent &e)
{
	for(int i = 0; i < mRootControls.size(); i++) {
		View *next = mRootControls[i];
		next->OnMouseEvent(e);
	}
}

/* IKeyboardListener methods */
void UIManager::OnKeyDown(const KeyboardEvent &e)
{
	ProcessKeyboardEvent(e);
}

void UIManager::OnKeyUp(const KeyboardEvent &e)
{
	ProcessKeyboardEvent(e);
}

void UIManager::OnKeyPress(const KeyboardEvent &e)
{
}

/* IMouseListener methods */
void UIManager::OnMouseDown(const MouseEvent &e)
{
	ProcessMouseEvent(e);
}

void UIManager::OnMouseUp(const MouseEvent &e)
{
	ProcessMouseEvent(e);
}

void UIManager::OnMouseMove(const MouseEvent &e)
{
	ProcessMouseEvent(e);
}

void UIManager::OnMouseClick(const MouseEvent &e)
{
	ProcessMouseEvent(e);
}

void UIManager::OnMouseDblClick(const MouseEvent &e)
{
	ProcessMouseEvent(e);
}