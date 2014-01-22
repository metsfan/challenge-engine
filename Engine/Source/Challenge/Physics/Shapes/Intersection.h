#pragma once

#include <Challenge/Challenge.h>
//#include <Challenge/Physics/Collision/CollisionData.h>

namespace challenge
{
	class AABBShape;
	class OBBShape;
	class TriangleShape;
	class TriangleMeshShape;

	class IntersectionTests 
	{
	public:
		//static bool SphereIntersectsSphere(const SphereShape *sphere1,const  SphereShape *sphere2, CollisionData *collision = NULL);
		//static bool AABBIntersectsSphere(const AABBShape *aabb, const SphereShape *sphere, CollisionData *collision = NULL);
		//static bool AABBIntersectsPlane(const AABBShape *aabb, const PlaneShape *plane, CollisionData *collision = NULL);
		static bool AABBIntersectsAABB(const AABBShape *aabb1, const AABBShape *aabb2, CollisionData *collision = NULL);
		static bool AABBIntersectsOBB(const AABBShape *aabb, const OBBShape *obb, CollisionData *collision = NULL);
		static bool AABBIntersectsTriangle(const AABBShape *aabb, const TriangleShape *triangle, CollisionData *collision = NULL);

		static bool OBBIntersectsOBB(const OBBShape *obb1, const OBBShape *obb2, CollisionData *collision = NULL);

	private:
		static bool BoxIntersect(const glm::mat3 &axes1, const glm::vec3 &dims1, 
			const glm::mat3 &axes2, const glm::vec3 &dims2, 
			const glm::vec3 &t);
	};
};

