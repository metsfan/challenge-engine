#pragma once

#include <Engine/Challenge.h>
#include <Engine/Scene/Plane.h>

namespace challenge
{
	typedef enum {
		PlaneNear,
		PlaneFar,
		PlaneTop,
		PlaneBottom,
		PlaneLeft,
		PlaneRight,
		NumPlanes
	} FrustumPlane;

	class Frustum
	{
	public:
		float mFov, mAspect, mNear, mFar;

		Frustum(void);
		Frustum(float n, float f, float e, float a);
		void Update(float n, float f, float e, float a);

		Plane GetNearPlane() { return mPlanes[PlaneNear]; }
		Plane GetFarPlane() { return mPlanes[PlaneFar]; }
		Plane GetTopPlane() { return mPlanes[PlaneTop]; }
		Plane GetBottomPlane() { return mPlanes[PlaneBottom]; }
		Plane GetLeftPlane() { return mPlanes[PlaneLeft]; }
		Plane GetRightPlane() { return mPlanes[PlaneRight]; }

		/* Collision detection */
		bool Contains(glm::vec3 point);
		bool Contains(glm::vec3 point, float radius);

		~Frustum(void);

	private:
		Plane mPlanes[NumPlanes];
	};
}

