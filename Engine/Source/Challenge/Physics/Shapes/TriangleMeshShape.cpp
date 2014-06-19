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

		mCollisionShape = new btBvhTriangleMeshShape(&mTriangles, true);
	}

	IGeometricShape* TriangleMeshShape::Clone()
	{
		return new TriangleMeshShape(*this);
	}

	void TriangleMeshShape::AddTriangle(const glm::vec3 &a, const glm::vec3 &b, const glm::vec3 &c)
	{
		mTriangles.addTriangle(ToBullet(a), ToBullet(b), ToBullet(c));
	}

	void TriangleMeshShape::DrawDebug(IGraphicsDevice *device, RenderState &state)
	{
		if (mDebugTriangle) {
			mDebugTriangle->DrawDebug(device, state);
		}
	}
};