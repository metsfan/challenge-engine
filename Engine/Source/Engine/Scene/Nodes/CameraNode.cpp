#include <Engine/Challenge.h>
#include <d3dx9math.h>
#include "CameraNode.h"
using namespace challenge;

CameraNode::CameraNode(glm::mat4 *t, Frustum *frustum) : SceneNode("", "Camera", RenderPassStatic, t, NULL)
{
	mFrustum = *frustum;
	mProjectionMatrix = glm::perspective(frustum->mFov, frustum->mAspect, frustum->mNear, frustum->mFar);

	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovRH(&proj, frustum->mFov, frustum->mAspect, frustum->mNear, frustum->mFar);

	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			mProjectionMatrix[i][j] = proj.m[i][j];
		}
	}
	
	mViewMatrix = *t;
}

void CameraNode::Render(Scene *pScene)
{

}
void CameraNode::SetView(Scene *pScene)
{
	if(mTarget) {
		glm::mat4 targetMatrix = mTarget->GetProps().ToWorld();
		//glm::mat4 cameraMatrix = targetMatrix;
		glm::mat4 cameraMatrix = glm::rotate(targetMatrix, -10.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		cameraMatrix = glm::translate(cameraMatrix, glm::vec3(0.0f, 1.5f, 10.0f));

		//cameraMatrix = glm::mat4(1.0f);
		//cameraMatrix = glm::translate(cameraMatrix, glm::vec3(0.0, -4.0, 0.0));
		this->SetTransform(&cameraMatrix, NULL);
	}
	mViewMatrix = this->GetProps().FromWorld();
}