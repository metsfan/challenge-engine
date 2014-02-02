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

		std::vector<OctreeObject> shapes = mDataTree->Query(other);
		for (OctreeObject &obj : shapes) {
			//for (const TriangleShape &triangle : mTriangles) {
			const TriangleShape *triangle = dynamic_cast<const TriangleShape *>(obj.shape);

			bool collides = triangle->Intersects(other, collision);

			if (collides) {
				hasCollision = true;

				mDebugTriangle = const_cast<TriangleShape *>(triangle);
			}
		}

		return hasCollision;
	}

	bool TriangleMeshShape::Intersects(const AABBShape *aabb, CollisionData *collision) const
	{
		bool hasCollision = false;

		if (this->GetPosition().x != 0) {
			int x = 0;
		}

		std::vector<OctreeObject> shapes = mDataTree->Query(aabb);
		for (OctreeObject &obj : shapes) {
		//for (const TriangleShape &triangle : mTriangles) {
			const TriangleShape *triangle = dynamic_cast<const TriangleShape *>(obj.shape);

			bool collides = IntersectionTests::AABBIntersectsTriangle(aabb, triangle, collision);

			if (collides) {
				hasCollision = true;

				mDebugTriangle = const_cast<TriangleShape *>(triangle);
			}
		}

		return hasCollision;
	}

	bool TriangleMeshShape::RayIntersects(const Ray &ray, float &t) const
	{
		float minT = INFINITY;
		bool intersects = false;

		for (const TriangleShape *triangle : mTriangles) {
			if (triangle->RayIntersects(ray, t)) {
				intersects = true;
				minT = glm::min(minT, t);
			}
		}

		t = minT;
		return intersects;
	}

	void TriangleMeshShape::AddTriangle(const glm::vec3 &a, const glm::vec3 &b, const glm::vec3 &c)
	{
		TriangleShape *triangle = new TriangleShape(a, b, c);
		triangle->SetPosition(this->GetPosition());
		mTriangles.push_back(triangle);
		mDataTree->AddShape(mTriangles.back(), this);
	}

	void TriangleMeshShape::DrawDebug(IGraphicsDevice *device, RenderState &state)
	{
		if (mDebugTriangle) {
			mDebugTriangle->DrawDebug(device, state);
		}
	}

	void TriangleMeshShape::SetPosition(glm::vec3 position)
	{
		GeometricShape::SetPosition(position);

		for (TriangleShape *triangle : mTriangles) {
			triangle->SetPosition(position);
		}
	}
};