#include <Engine/Challenge.h>
#include "Frustum.h"
using namespace challenge;

Frustum::Frustum(void)
{
}

Frustum::Frustum(float n, float f, float e, float a)
{
	this->Update(n, f, e, a);
}

void Frustum::Update(float n, float f, float e, float a) 
{
	float e_sq = e*e;
	float a_sq = a*a;
	float e_sq_plus_1 = sqrt(e_sq + 1);
	float e_sq_a_sq = sqrt(e_sq + a_sq);

	mPlanes[PlaneNear] = Plane(0, 0, -1, -n);
	mPlanes[PlaneFar] = Plane(0, 0, 1, f);

	mPlanes[PlaneLeft] = Plane(e / e_sq_plus_1, 0, -1.0 /  e_sq_plus_1, 0);
	mPlanes[PlaneRight] = Plane(-e / e_sq_plus_1, 0, -1.0 / e_sq_plus_1, 0);

	mPlanes[PlaneBottom] = Plane(0, e / e_sq_a_sq, -a / e_sq_a_sq, 0);
	mPlanes[PlaneTop] = Plane(0, -e / e_sq_a_sq, -a / e_sq_a_sq, 0);

	mNear = n;
	mFar = f;
	mFov = e;
	mAspect = a;
}

bool Frustum::Contains(glm::vec3 point)
{
	for(int i = 0; i < NumPlanes; i++) {
		if(!mPlanes[i].Contains(point)) {
			return false;
		}
	}
	return true;
}

bool Frustum::Contains(glm::vec3 point, float radius)
{
	for(int i = 0; i < NumPlanes; i++) {
		if(!mPlanes[i].Contains(point, radius)) {
			return false;
		}
	}
	return true;
}

Frustum::~Frustum(void)
{
}
