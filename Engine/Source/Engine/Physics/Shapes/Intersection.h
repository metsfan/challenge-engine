#pragma once

#include <Engine/Challenge.h>
#include "SphereShape.h"
#include "AABBShape.h"
#include "PlaneShape.h"
#include "TriangleShape.h"
#include <Engine/Physics/Collision/CollisionData.h>

namespace challenge
{
	class IntersectionTests 
	{
	public:
		static bool SphereIntersectsSphere(SphereShape *sphere1, SphereShape *sphere2, CollisionData *collision = NULL);
		static bool AABBIntersectsSphere(AABBShape *aabb, SphereShape *sphere, CollisionData *collision = NULL);
		static bool AABBIntersectsPlane(AABBShape *aabb, PlaneShape *plane, CollisionData *collision = NULL);
		static bool AABBIntersectsAABB(AABBShape *aabb1, AABBShape *aabb2, CollisionData *collision = NULL);
		static bool AABBIntersectsTriangle(AABBShape *aabb, TriangleShape *triangle, CollisionData *collision = NULL);
	};
};

