#include <Engine/Challenge.h>
#include "Math.h"
using namespace challenge;

float PhysicsMath::PointPlaneDistance(const glm::vec3 &point, const PlaneShape *plane)
{
	glm::vec4 p = plane->GetPlane();

	float a = (p.x * point.x) + (p.y * point.y) + (p.z * point.z) - p.w;
	float b = sqrt((p.x * p.x) + (p.y * p.y) + (p.z * p.z));

	return a / b;
}