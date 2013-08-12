#include <Engine/Challenge.h>
#include "ConcaveTriangleMeshShape.h"
#include "PlaneShape.h"
#include <Engine/Physics/Shapes/Intersection.h>
using namespace challenge;

ConcaveTriangleMeshShape::ConcaveTriangleMeshShape() : TriangleMeshShape()
{
	mDataTree = new Octree(2);
	mTreeSet = false;
}

bool ConcaveTriangleMeshShape::Intersects(IPhysicsShape *other, CollisionData *collision)
{
	bool hasCollision = false;

	if(mTreeSet) {
		PhysicsShapeType type = other->GetType();
	

		if(type == kShapeTypeAABB) {
			AABBShape *aabb = reinterpret_cast<AABBShape *>(other);

			/*TPhysicsShapeLinkedList shapes = mDataTree->FindNearestShapesToShape(aabb);
			TPhysicsShapeLinkedList::iterator it = shapes.begin();
			TPhysicsShapeLinkedList::iterator end = shapes.end();
			while(it != end) {
				TriangleShape *triangle = static_cast<TriangleShape *>(*it);
			
				bool collides = IntersectionTests::AABBIntersectsTriangle(aabb, triangle, collision);

				if(collides) {
					hasCollision = true;
				}

				++it;
			}*/
		}
	}

	return hasCollision;
}

void ConcaveTriangleMeshShape::AddTriangle(glm::vec3 a, glm::vec3 b, glm::vec3 c)
{
	TriangleMeshShape::AddTriangle(a, b, c);
}

void ConcaveTriangleMeshShape::CalculateDerivedData()
{
	TriangleMeshShape::CalculateDerivedData();

	if(!mTreeSet) {
		TPhysicsShapeLinkedList list;
		for(int i = 0; i < mTriangles.size(); i++) {
			list.push_back(mTriangles[i]);
		}
		//mDataTree->BuildTree(list);
		mTreeSet = true;
	}
}