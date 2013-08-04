#include <Engine/Challenge.h>
#include <Engine/Util/Util.h>
#include "Plane.h"
using namespace challenge;

Plane::Plane()
{
	mPlaneVec = glm::vec4(0, 0, 0, 0);
	mNormalVec = glm::vec3(0, 0, 0);
	mDist = 0;
}

Plane::Plane(float a, float b, float c, float d)
{
	glm::vec4 vec = glm::vec4(a, b, c, d);
	Initialize(vec);
}

Plane::Plane(glm::vec4 vec)
{
	Initialize(vec);
}

Plane::Plane(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3)
{
	glm::vec3 N = Util::CalculateFaceNormal(v1, v2, v3);
	float D = glm::dot(-N, v1);
	glm::vec4 vec = glm::vec4(N.x, N.y, N.z, D);
	Initialize(vec);
}

void Plane::Initialize(glm::vec4 vec)
{
	mPlaneVec = vec;
	mNormalVec = glm::vec3(vec.x, vec.y, vec.z);
	mDist = vec.w;
}

float Plane::DistanceFrom(glm::vec3 point)
{
	double d = glm::dot(mNormalVec, point) + mDist;
	return d;
}
bool Plane::Contains(glm::vec3 point)
{
	return DistanceFrom(point) == 0;
}
bool Plane::Contains(glm::vec3 point, float radius)
{
	double d = DistanceFrom(point);
	return (d >= -radius);
}