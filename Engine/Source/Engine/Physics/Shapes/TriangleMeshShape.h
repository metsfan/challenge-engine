#pragma once

#include <Engine/Challenge.h>
#include <Engine/Physics/Shapes/TriangleShape.h>
#include <Engine/Physics/Shapes/AABBShape.h>
#include <Engine/Physics/Shapes/SphereShape.h>

namespace challenge
{
	class TriangleMeshShape : public PhysicsShape
	{
	public:
		TriangleMeshShape();

		virtual bool Intersects(IPhysicsShape *other, CollisionData *collision = NULL);

		virtual void AddTriangle(glm::vec3 a, glm::vec3 b, glm::vec3 c);

		virtual PhysicsShapeType GetType() { return kShapeTypeTriangleMesh; }

		virtual void SetPosition(glm::vec3 position);
		virtual glm::mat3 CalculateInertiaTensor(float mass);

		virtual void CalculateDerivedData(); 

	protected:
		TTriangleList mTriangles;
		AABBShape mBoundingBox;
		SphereShape mBoundingSphere;
		real mMinX, mMinY, mMinZ, mMaxX, mMaxY, mMaxZ;
		bool mMeshChanged;

		void CalculateBoundingSphere();
		void CalculateBoundingBox();
	};
};