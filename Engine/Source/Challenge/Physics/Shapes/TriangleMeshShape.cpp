#include <Challenge/Challenge.h>
#include "TriangleMeshShape.h"
#include "PlaneShape.h"
#include <Challenge/Physics/Shapes/Intersection.h>
#include <Challenge/Physics/BVH/Octree.h>
#include <Challenge/Physics/Shapes/TriangleShape.h>

namespace challenge
{
	IGeometricShape* TriangleMeshShape::CreateFromPointsList(const std::vector<glm::vec3> &points)
	{
		TriangleMeshShape *shape = new TriangleMeshShape();
		for(int i = 0; i < points.size(); i+=3) {
			shape->AddTriangle(points[i], points[i+1], points[i+2]);
		}

		return shape;
	}

	TriangleMeshShape::TriangleMeshShape() : 
		GeometricShape(),
		mDebugTriangle(NULL)
	{
		mDataTree = new Octree(BoundingBox(-1000, -1000, -1000, 1000, 1000, 1000), 3);
	}

	IGeometricShape* TriangleMeshShape::Clone()
	{
		return new TriangleMeshShape(*this);
	}

	bool TriangleMeshShape::Intersects(const IGeometricShape *other, CollisionData *collision) const
	{
		bool hasCollision = false;

		GeometricShapeType type = other->GetType();
	

		if(type == kShapeTypeAABB) {
			const AABBShape *aabb = reinterpret_cast<const AABBShape *>(other);
			return this->Intersects(aabb, collision);
		}
		
		return false;
	}

	bool TriangleMeshShape::Intersects(const AABBShape *aabb, CollisionData *collision) const
	{
		bool hasCollision = false;

		//std::vector<OctreeObject> shapes = mDataTree->Query(aabb);
		//for (OctreeObject &obj : shapes) {
		for (const TriangleShape &triangle : mTriangles) {
			//TriangleShape *triangle = dynamic_cast<TriangleShape *>(obj.shape);

			bool collides = IntersectionTests::AABBIntersectsTriangle(aabb, &triangle, collision);

			if (collides) {
				hasCollision = true;

				mDebugTriangle = const_cast<TriangleShape *>(&triangle);
			}
		}

		return hasCollision;
	}

	bool TriangleMeshShape::RayIntersects(const Ray &ray, float &t) const
	{
		float minT = INFINITY;
		bool intersects = false;

		for (const TriangleShape &triangle : mTriangles) {
			if (triangle.RayIntersects(ray, t)) {
				intersects = true;
				minT = glm::min(minT, t);
			}
		}

		t = minT;
		return intersects;
	}

	void TriangleMeshShape::AddTriangle(const glm::vec3 &a, const glm::vec3 &b, const glm::vec3 &c)
	{
		mTriangles.push_back(TriangleShape(a, b, c));
		mDataTree->AddShape(&mTriangles.back(), this);
	}

	void TriangleMeshShape::DrawDebug(IGraphicsDevice *device, RenderState &state)
	{
		if (mDebugTriangle) {
			mDebugTriangle->DrawDebug(device, state);
		}
	}
};