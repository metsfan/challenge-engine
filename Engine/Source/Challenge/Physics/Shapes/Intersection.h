#pragma once

#include <Challenge/Challenge.h>
//#include <Challenge/Physics/Collision/CollisionData.h>

namespace challenge
{
	class BoxShape;
	class OBBShape;
	class TriangleShape;
	class TriangleMeshShape;
	class SphereShape;

	class IntersectionTests 
	{
	public:
		//static bool SphereIntersectsSphere(const SphereShape *sphere1,const  SphereShape *sphere2, CollisionData *collision = NULL);
		static bool AABBIntersectsSphere(const BoxShape *aabb, const SphereShape *sphere, CollisionData *collision = NULL);
		//static bool AABBIntersectsPlane(const BoxShape *aabb, const PlaneShape *plane, CollisionData *collision = NULL);
		static bool AABBIntersectsAABB(const BoxShape *aabb1, const BoxShape *aabb2, CollisionData *collision = NULL);
		static bool AABBIntersectsOBB(const BoxShape *aabb, const OBBShape *obb, CollisionData *collision = NULL);
		static bool AABBIntersectsTriangle(const BoxShape *aabb, const TriangleShape *triangle, CollisionData *collision = NULL);

		static bool OBBIntersectsOBB(const OBBShape *obb1, const OBBShape *obb2, CollisionData *collision = NULL);

	private:
		static bool BoxIntersect(const glm::mat3 &axes1, const glm::vec3 &dims1, 
			const glm::mat3 &axes2, const glm::vec3 &dims2, 
			const glm::vec3 &t);
		static void UpdateSATPenetration(real min1, real max1,
			real min2, real max2,
			const glm::vec3 &axis, real &min, glm::vec3 &minAxis);
	};
};

