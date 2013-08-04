#include <Engine/Challenge.h>
#include <Engine/UI/UIManager.h>
#include <Engine/Util/Image.h>
//#include <Engine/Util/TextureAtlas.h>
#include <Engine/Renderer/Texture/Texture2DDX11.h>
#include <Engine/GameApplication.h>
#include <Engine/Renderer/Window.h>
#include "View.h"
using namespace challenge;

View::View() :
	mFrame(Frame(0, 0, 0, 0)),
	mAdjustedFrame(mFrame),
	mVisible(true),
	mZPosition(0),
	mBackgroundImage(NULL),
	mParent(NULL)
{
}

View::View(Frame frame) :
	mFrame(frame),
	mAdjustedFrame(frame),
	mVisible(true),
	mZPosition(0),
	mBackgroundImage(NULL),
	mParent(NULL)
{
}

View::~View()
{
}

void View::AddSubcontrol(View *control)
{
	bool found = false;
	for(int i = 0; i < mSubcontrols.size(); i++) {
		if(mSubcontrols[i] == control) {
			found = true;
		}
	}

	if(!found) {
		mSubcontrols.push_back(control);
		control->SetParent(this);
		control->SetZPosition(mZPosition + 1);
		UIManager *uiManager = UIManager::GetDefaultManager();
		uiManager->AddControl(control);
	}
}

void View::UpdateBase(int deltaMillis)
{
	Update(deltaMillis);

	for(int j = 0; j < mSubcontrols.size(); j++) {
		mSubcontrols[j]->UpdateBase(deltaMillis);
	}
}

void View::RenderBase(UIManager *manager, Point origin)
{
	if(mVisible) {
		// Apply derived class logic
		Render(manager, origin);

		Frame adjustedFrame = mFrame;
		adjustedFrame.origin.x += origin.x;
		adjustedFrame.origin.y += origin.y;

		glm::mat4 modelViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(adjustedFrame.origin.x, adjustedFrame.origin.y, 0.0f));
		modelViewMatrix = glm::scale(modelViewMatrix, glm::vec3(adjustedFrame.size.width, adjustedFrame.size.height, 1.0f));
		//modelViewMatrix = glm::transpose(modelViewMatrix);

		glm::mat4 modelViewProjectionMatrix = manager->mProjectionMatrix * modelViewMatrix;
		mMatrices.gWVPMatrix = modelViewProjectionMatrix;
		//manager->mShader->setUniform("ModelViewProjectionMatrix", modelViewProjectionMatrix);

		glm::vec4 bgColorVec = glm::vec4(mBackgroundColor.red, mBackgroundColor.green, mBackgroundColor.blue, mBackgroundColor.alpha);
		mControlData.gBackgroundColor = bgColorVec;
		//manager->mShader->setUniform("BackgroundColor", bgColorVec);

		if(mBackgroundImage != NULL) {
			mControlData.gHasTexture = 1;
			//mBackgroundImage->Activate(GL_TEXTURE0);
			//manager->mShader->setUniform("BackgroundImage", 0);
			//manager->mShader->setUniform("HasTexture", 1);
		} else {
			mControlData.gHasTexture = 0;
			//manager->mShader->setUniform("HasTexture", 0);
		}
		//manager->mShader->setUniform("HasText", 0);

		//glDrawArrays(GL_QUADS, 0, 4);

		RendererType rendererType = GameApplication::GetInstance()->GetRendererType();

		/*if(rendererType == RendererTypeDX11) {
			HLSLProgram *shader = manager->GetShader();

			shader->SetConstantBuffer(&mMatrices, sizeof(ControlMatrices), 0, HLSLShaderTypeVertex);
			shader->SetConstantBuffer(&mControlData, sizeof(ControlData), 0, HLSLShaderTypePixel);

			if(mControlData.gHasTexture) {
				TextureDX11 *dxTexture = reinterpret_cast<TextureDX11 *>(mBackgroundImage);
				shader->SetResource(dxTexture->GetTextureResource(), 0, 1, HLSLShaderTypePixel);
			}
		}

		Renderer *renderer = GameApplication::GetInstance()->GetWindow()->GetRenderer();
		renderer->Draw(PrimitiveTypeTriangleStrip, 0, 4);*/

		origin = adjustedFrame.origin;

		for(int i = 0; i < mSubcontrols.size(); i++) {
			View *child = mSubcontrols[i];
			child->RenderBase(manager, origin);
		}
	}
}

void View::SetBackgroundImage(std::string imageName)
{
	//mBackgroundImage = imageName;

	Image *image = new Image(imageName);
	//UIManager::GetDefaultManager()->AddImageToAtlas(image);
	//mBackgroundImage = new Texture();
	//TextureInfo texInfo = Texture::DefaultTextureInfo();
	//texInfo.format = GL_BGR;
	//texInfo.internalFormat = GL_RGB;
	//mBackgroundImage->Initialize(image->GetBits(), image->GetWidth(), image->GetHeight());
}

/* Event Delegates */

void View::AddMouseDownDelegate(MouseEventDelegate eventDelegate)
{
	mMouseDelegates[MouseEventMouseDown].push_back(eventDelegate);
}

void View::AddMouseUpDelegate(MouseEventDelegate eventDelegate)
{
	mMouseDelegates[MouseEventMouseUp].push_back(eventDelegate);
}

void View::AddMouseClickDelegate(MouseEventDelegate eventDelegate)
{
	mMouseDelegates[MouseEventMouseClick].push_back(eventDelegate);
}

void View::AddMouseMoveDelegate(MouseEventDelegate eventDelegate)
{
	mMouseDelegates[MouseEventMouseMove].push_back(eventDelegate);
}

void View::AddKeyDownDelegate(KeyboardEventDelegate eventDelegate)
{
	mKeyboardDelegates[KeyboardEventKeyDown].push_back(eventDelegate);
}

void View::AddKeyUpDelegate(KeyboardEventDelegate eventDelegate)
{
	mKeyboardDelegates[KeyboardEventKeyUp].push_back(eventDelegate);
}

bool View::OnMouseEvent(const MouseEvent &e)
{
	bool handled = false;
	if(mSubcontrols.size() > 0) {
		View *topControl = NULL;
		for(int i = mSubcontrols.size() - 1; i >= 0; i--) {
			View *next = mSubcontrols[i];
			if(next->ProcessMouseEvent(e)) {
				if(topControl == NULL ||
					topControl->mZPosition < next->mZPosition) {
					topControl = next;
				}
			}
		}

		if(topControl != NULL) {
			topControl->OnMouseEvent(e);
			handled = true;
		}
	}
	
	if(!handled) {
		if(mMouseDelegates.size() > 0 && ProcessMouseEvent(e)) {
			std::vector<MouseEventDelegate> delegates = mMouseDelegates[e.type];

			for(int i = 0; i < delegates.size(); i++) {
				delegates[i](this, e);
			}

			return true;
		}
	}

	return false;
}

bool View::ProcessMouseEvent(const MouseEvent &e)
{
	return ContainsPoint(e.position);
}

bool View::OnKeyboardEvent(const KeyboardEvent &e)
{
	if(mKeyboardDelegates.size() > 0 && ProcessKeyboardEvent(e)) {
		std::vector<KeyboardEventDelegate> delegates = mKeyboardDelegates[e.type];

		for(int i = 0; i < delegates.size(); i++) {
			delegates[i](this, e);
		}

		return true;
	}

	for(int i = 0; i < mSubcontrols.size(); i++) {
		if(mSubcontrols[i]->OnKeyboardEvent(e)) {
			return true;
		}
	}

	return false;
}

bool View::ProcessKeyboardEvent(const KeyboardEvent &e)
{
	return false; // Keyboard events are undefined for default controls
}