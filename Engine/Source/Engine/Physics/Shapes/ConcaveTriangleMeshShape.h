#pragma once

#include <Engine/Challenge.h>
#include <Engine/Physics/Shapes/TriangleMeshShape.h>
#include <Engine/Physics/BVH/Octree.h>

namespace challenge
{
	class ConcaveTriangleMeshShape : public TriangleMeshShape
	{
	public:
		ConcaveTriangleMeshShape();

		virtual bool Intersects(IPhysicsShape *other, CollisionData *collision = NULL);

		virtual PhysicsShapeType GetType() { return kShapeTypeConcaveTriangleMesh; } 

		virtual void AddTriangle(glm::vec3 a, glm::vec3 b, glm::vec3 c);
		virtual void CalculateDerivedData(); 

	private:
		Octree *mDataTree;
		bool mTreeSet;
	};
};