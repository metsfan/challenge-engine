#pragma once

#include <Engine/Challenge.h>
#include <Engine/Scene/SceneNode.h>
#include <Engine/Scene/Frustum.h>

namespace challenge
{
	class CameraNode : public SceneNode
	{
	public:
		CameraNode(glm::mat4 *t, Frustum *frustum);
		virtual void Render(Scene *pScene);
		virtual void SetView(Scene *pScene);

		const Frustum GetFrustum() { return mFrustum; }

		void SetTarget(SceneNode *pTarget) { mTarget = pTarget; }

		glm::mat4 GetViewMatrix() { return mViewMatrix; }
		glm::mat4 GetProjectionMatrix() { return mProjectionMatrix; }

	protected:
		Frustum mFrustum;
		glm::mat4 mProjectionMatrix;
		glm::mat4 mViewMatrix;
		
		bool mActive;
		bool mDebugCamera;
		SceneNode *mTarget;
	};
};