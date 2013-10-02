#pragma once

#include <Engine/Challenge.h>
#include <Engine/Physics/Shapes/TriangleMeshShape.h>


namespace challenge
{
	class Octree;

	class ConcaveTriangleMeshShape : public TriangleMeshShape
	{
	public:
		ConcaveTriangleMeshShape();

		virtual bool Intersects(IGeometricShape *other, CollisionData *collision = NULL);

		virtual GeometricShapeType GetType() { return kShapeTypeConcaveTriangleMesh; } 

		virtual void AddTriangle(const glm::vec3 &a, const glm::vec3 &b, const glm::vec3 &c);
		virtual void CalculateDerivedData(); 

		static IGeometricShape* CreateFromPointsList(const std::vector<glm::vec3> &points);

		IGeometricShape* Clone();

	private:
		Octree *mDataTree;
		bool mTreeSet;
	};
};