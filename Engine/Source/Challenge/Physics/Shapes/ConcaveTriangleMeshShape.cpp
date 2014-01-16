#include <Challenge/Challenge.h>
#include "ConcaveTriangleMeshShape.h"
#include "PlaneShape.h"
#include <Challenge/Physics/Shapes/Intersection.h>
#include <Challenge/Physics/BVH/Octree.h>

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
		mDataTree = new Octree(BoundingBox(-1000, -1000, -1000, 1000, 1000, 1000), 3);
	}

	IGeometricShape* ConcaveTriangleMeshShape::Clone()
	{
		return new ConcaveTriangleMeshShape(*this);
	}

	bool ConcaveTriangleMeshShape::Intersects(IGeometricShape *other, CollisionData *collision) const
	{
		bool hasCollision = false;

		GeometricShapeType type = other->GetType();
	

		if(type == kShapeTypeAABB) {
			AABBShape *aabb = reinterpret_cast<AABBShape *>(other);

			std::vector<OctreeObject> shapes = mDataTree->Query(aabb);
			for (OctreeObject &obj : shapes) {
				TriangleShape *triangle = dynamic_cast<TriangleShape *>(obj.shape);
			
				bool collides = IntersectionTests::AABBIntersectsTriangle(aabb, triangle, collision);

				if(collides) {
					hasCollision = true;
				}
			}
		}
		

		return hasCollision;
	}

	void ConcaveTriangleMeshShape::AddTriangle(const glm::vec3 &a, const glm::vec3 &b, const glm::vec3 &c)
	{
		TriangleMeshShape::AddTriangle(a, b, c);

		mDataTree->AddShape(mTriangles.back(), this);
	}
};