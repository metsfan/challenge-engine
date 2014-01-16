#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Physics/Shapes/TriangleMeshShape.h>


namespace challenge
{
	class Octree;

	class ConcaveTriangleMeshShape : public TriangleMeshShape
	{
	public:
		ConcaveTriangleMeshShape();

		virtual bool Intersects(IGeometricShape *other, CollisionData *collision = NULL) const;

		virtual GeometricShapeType GetType() const { return kShapeTypeConcaveTriangleMesh; } 

		virtual void AddTriangle(const glm::vec3 &a, const glm::vec3 &b, const glm::vec3 &c);

		static IGeometricShape* CreateFromPointsList(const std::vector<glm::vec3> &points);

		IGeometricShape* Clone();

	private:
		Octree *mDataTree;
		bool mTreeSet;
	};
};