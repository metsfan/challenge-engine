#pragma once

#include <Engine/Challenge.h>
#include <Engine/Physics/Shapes/TriangleShape.h>
#include <Engine/Physics/Shapes/AABBShape.h>
#include <Engine/Physics/Shapes/SphereShape.h>

namespace challenge
{
	class TriangleMeshShape : public GeometricShape
	{
	public:
		TriangleMeshShape();

		virtual bool Intersects(IGeometricShape *other, CollisionData *collision = NULL) const;

		virtual void AddTriangle(const glm::vec3 &a, const glm::vec3 &b, const glm::vec3 &c);

		virtual GeometricShapeType GetType() const { return kShapeTypeTriangleMesh; }

		virtual void SetPosition(glm::vec3 position);
		virtual glm::mat3 CalculateInertiaTensor(float mass);

		virtual void CalculateDerivedData(); 

		static IGeometricShape* CreateFromPointsList(const std::vector<glm::vec3> &points);

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