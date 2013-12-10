#pragma once

#include <Challenge/Challenge.h>
#include "SphereShape.h"
#include "AABBShape.h"
#include "PlaneShape.h"
#include "TriangleShape.h"
#include <Challenge/Physics/Collision/CollisionData.h>

namespace challenge
{
	class IntersectionTests 
	{
	public:
		static bool SphereIntersectsSphere(const SphereShape *sphere1,const  SphereShape *sphere2, CollisionData *collision = NULL);
		static bool AABBIntersectsSphere(const AABBShape *aabb, const SphereShape *sphere, CollisionData *collision = NULL);
		static bool AABBIntersectsPlane(const AABBShape *aabb, const PlaneShape *plane, CollisionData *collision = NULL);
		static bool AABBIntersectsAABB(const AABBShape *aabb1, const AABBShape *aabb2, CollisionData *collision = NULL);
		static bool AABBIntersectsTriangle(const AABBShape *aabb, const TriangleShape *triangle, CollisionData *collision = NULL);
	};
};

