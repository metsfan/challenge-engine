#include <Engine/Challenge.h>
#include "Camera.h"

namespace challenge
{
	Camera::Camera(glm::mat4 projectionMatrix, Size screenSize) :
		mProjectionMatrix(projectionMatrix),
		mScreenSize(screenSize),
		mScale(1),
		mShear(0),
		mViewChanged(true),
		mViewport(0.0f, 0.0f, (float)screenSize.width, (float)screenSize.height),
		mAspect((float)screenSize.width / (float)screenSize.height)
	{
	}

	void Camera::MoveBy(glm::vec3 delta)
	{
		mPosition += delta;
		mViewChanged = true;
	}

	void Camera::MoveTo(glm::vec3 position)
	{
		mPosition = position;
		mViewChanged = true;
	}

	void Camera::RotateBy(glm::vec3 delta)
	{
		mRotation += delta;

		if (mRotation.x < 0) {
			mRotation.x += 360;
		} else if (mRotation.x > 360) {
			mRotation.x -= 360;
		}
    
		if (mRotation.y < 0) {
			mRotation.y += 360;
		} else if (mRotation.y > 360) {
			mRotation.y -= 360;
		}
    
		if (mRotation.z < 0) {
			mRotation.z += 360;
		} else if (mRotation.z > 360) {
			mRotation.z -= 360;
		}
    
		mViewChanged = true;
	}

	void Camera::RotateTo(glm::vec3 rotation)
	{
		mRotation = rotation;
    
		if (mRotation.x < 0) {
			mRotation.x += 360;
		} else if (mRotation.x > 360) {
			mRotation.x -= 360;
		}
    
		if (mRotation.y < 0) {
			mRotation.y += 360;
		} else if (mRotation.y > 360) {
			mRotation.y -= 360;
		}
    
		if (mRotation.z < 0) {
			mRotation.z += 360;
		} else if (mRotation.z > 360) {
			mRotation.z -= 360;
		}
    
		mViewChanged = true;
	}

	void Camera::ScaleBy(real delta)
	{
		mScale *= delta;
	}

	void Camera::ScaleTo(real scale)
	{
		mScale = scale;
	}

	void Camera::ShearBy(real delta)
	{
		mShear += delta;
	}

	void Camera::ShearTo(real shear)
	{
		mShear = shear;
	}

	Point Camera::Project(glm::vec3 point)
    {
		glm::vec3 pt = glm::project(point, mInverseViewMatrix, mProjectionMatrix, mViewport);
		return Point(pt.x, pt.y);
    }
    
    glm::vec3 Camera::Unproject(Point screenPos, real zPos)
    {
		glm::vec3 win(screenPos.x, mScreenSize.height - screenPos.y, zPos);
		glm::vec3 pt = glm::unProject(win, mInverseViewMatrix, mProjectionMatrix, mViewport);

		/*float dx = (2 * screenPos.x / mScreenSize.width - 1);
        float dy = (1 - 2 * screenPos.y / mScreenSize.height);
        
        glm::vec4 p = glm::vec4(dx, dy, zPos, 1.0);
        glm::vec3 pt = glm::vec3(mInverseViewProjectionMatrix * p);*/

		return pt;
    }

	void Camera::LookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up)
	{
		glm::vec3 zAxis = glm::normalize(center - eye);
		glm::vec3 xAxis = glm::normalize(glm::cross(up, zAxis));
		glm::vec3 yAxis = glm::cross(zAxis, xAxis);

		glm::mat4 orientation = glm::mat4(
			xAxis.x, yAxis.x, zAxis.x, 0,
			xAxis.y, yAxis.y, zAxis.y, 0,
			xAxis.z, yAxis.z, zAxis.z, 0,
			0, 0, 0, 1
		);

		glm::mat4 translation = glm::mat4(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			-eye.x, -eye.y, -eye.z, 1
		);

		mViewMatrix = translation * orientation;
	}

	void Camera::Update()
	{
		//if (mViewChanged) 
		//{
			mViewMatrix = glm::mat4();

			mViewMatrix = glm::translate(mViewMatrix, mPosition);
			
			if (mRotation.y) {
				mViewMatrix = glm::rotate(mViewMatrix, mRotation.y, glm::vec3(0, 1, 0));
			}

			if (mRotation.x) {
				mViewMatrix = glm::rotate(mViewMatrix, mRotation.x, glm::vec3(1, 0, 0));
			}

			if (mRotation.z) {
				mViewMatrix = glm::rotate(mViewMatrix, mRotation.z, glm::vec3(0, 0, 1));
			}
			
        
			if (mShear != 0.0) {
				mViewMatrix = glm::scale(mViewMatrix, glm::vec3(0, mScale, 0));
				mViewMatrix[1][2] *= mShear;
			}

			mInverseViewMatrix = glm::inverse(mViewMatrix);
			mViewProjectionMatrix = mProjectionMatrix * mInverseViewMatrix;
			mInverseViewProjectionMatrix = glm::inverse(mViewProjectionMatrix);
        
			mViewChanged = false;
		//}
	}
};


