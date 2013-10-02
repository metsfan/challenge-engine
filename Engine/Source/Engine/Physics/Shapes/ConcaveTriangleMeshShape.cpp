#include <Engine/Challenge.h>
#include "ConcaveTriangleMeshShape.h"
#include "PlaneShape.h"
#include <Engine/Physics/Shapes/Intersection.h>
#include <Engine/Physics/BVH/Octree.h>

namespace challenge
{
	IGeometricShape* ConcaveTriangleMeshShape::CreateFromPointsList(const std::vector<glm::vec3> &points)
	{
		ConcaveTriangleMeshShape *shape = new ConcaveTriangleMeshShape();
		for(int i = 0; i < points.size(); i+=3) {
			shape->AddTriangle(points[i], points[i+1], points[i+2]);
		}

		return shape;
	}

	ConcaveTriangleMeshShape::ConcaveTriangleMeshShape() : TriangleMeshShape()
	{
		mDataTree = new Octree(BoundingBox(), 2);
		mTreeSet = false;
	}

	IGeometricShape* ConcaveTriangleMeshShape::Clone()
	{
		return new ConcaveTriangleMeshShape(*this);
	}

	bool ConcaveTriangleMeshShape::Intersects(IGeometricShape *other, CollisionData *collision)
	{
		bool hasCollision = false;

		if(mTreeSet) {
			GeometricShapeType type = other->GetType();
	

			if(type == kShapeTypeAABB) {
				AABBShape *aabb = reinterpret_cast<AABBShape *>(other);

				/*TGeometricShapeLinkedList shapes = mDataTree->FindNearestShapesToShape(aabb);
				TGeometricShapeLinkedList::iterator it = shapes.begin();
				TGeometricShapeLinkedList::iterator end = shapes.end();
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

	void ConcaveTriangleMeshShape::AddTriangle(const glm::vec3 &a, const glm::vec3 &b, const glm::vec3 &c)
	{
		TriangleMeshShape::AddTriangle(a, b, c);
	}

	void ConcaveTriangleMeshShape::CalculateDerivedData()
	{
		TriangleMeshShape::CalculateDerivedData();

		if(!mTreeSet) {
			TGeometricShapeLinkedList list;
			for(int i = 0; i < mTriangles.size(); i++) {
				list.push_back(mTriangles[i]);
			}
			//mDataTree->BuildTree(list);
			mTreeSet = true;
		}
	}
};