#pragma once

#include <Engine/Challenge.h>

namespace challenge
{
	class Camera
	{
	public:
        Camera(glm::mat4 projectionMatrix, Size screenSize);
		virtual ~Camera() {}
        
        virtual void MoveBy(glm::vec3 delta);
        virtual void MoveTo(glm::vec3 position);
        
        virtual void RotateBy(glm::vec3 delta);
        virtual void RotateTo(glm::vec3 rotation);
        
        virtual void ScaleBy(real delta);
        virtual void ScaleTo(real scale);
        
        virtual void ShearBy(real delta);
        virtual void ShearTo(real shear);
        
        Point Project(glm::vec3 point);
        glm::vec3 Unproject(Point screenPos, real zPos);

		void LookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up = glm::vec3(0, 1, 0));
        
        virtual void Update();
        
        const glm::mat4 GetProjectionMatrix() const { return mProjectionMatrix; }
        const glm::mat4 GetViewMatrix() const { return mViewMatrix; }
		const glm::mat4& GetInverseViewMatrix() const { return mInverseViewMatrix; }
        
        const glm::vec3& GetPosition() const { return mPosition; }
        const glm::vec3& GetRotation() const { return mRotation; }

		float GetAspect() { return mAspect; }
        const Size& GetScreenSize() const { return mScreenSize; }

    protected:
        const real GetScale() const { return mScale; }
        const real GetShear() const { return mShear; }
        
        
        void SetProjectionMatrix(glm::mat4 m) { mProjectionMatrix = m; }

	private:
		glm::mat4 mViewMatrix;
		glm::mat4 mInverseViewMatrix;
		glm::mat4 mProjectionMatrix;
		glm::mat4 mViewProjectionMatrix;
		glm::mat4 mInverseViewProjectionMatrix;
		glm::vec3 mPosition;
		glm::vec3 mRotation;
		glm::vec4 mViewport;
		real mScale;
		real mShear;
		real mAspect;
		Frame mBounds;
		Size mScreenSize;
        bool mViewChanged;
	};
};