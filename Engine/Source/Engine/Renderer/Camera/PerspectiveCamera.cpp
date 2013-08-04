
#include <Engine/Challenge.h>
#include "PerspectiveCamera.h"


namespace challenge
{
	PerspectiveCamera::PerspectiveCamera(real aspect, real fovy, real nearZ, real farZ, Size screenSize) :
		Camera(glm::perspective(fovy, aspect, nearZ, farZ), screenSize),
		mAspect(aspect),
		mFovY(fovy),
		mNearZ(nearZ),
		mFarZ(farZ)
	{
	}

	void PerspectiveCamera::Update()
	{
		Camera::Update();
    
		//glm::mat4 projMatrix = this->GetProjectionMatrix();
		//glm::mat4 viewMatrix = this->GetViewMatrix();
		//mFrustum.UpdatePlanes(projMatrix * viewMatrix);
	}
}

