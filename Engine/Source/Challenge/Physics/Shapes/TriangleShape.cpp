#include <Challenge/Challenge.h>
//#include <Challenge/Physics/Shapes/Intersection.h>
#include "TriangleShape.h"

namespace challenge
{
	TriangleShape::TriangleShape(glm::vec3 a, glm::vec3 b, glm::vec3 c) :
		mTriangle(a, b, c)
	{
		//this->CalculateNormal();
		this->CalculateBoundingBox();
	}

	void TriangleShape::CalculateBoundingBox()
	{
		float minX, minY, minZ, maxX, maxY, maxZ;
		minX = minY = minZ = INFINITY;
		maxX = maxY = maxZ = -INFINITY;

		for(int i = 0; i < 3; i++) {
			if (mTriangle[i].x < minX) minX = mTriangle[i].x;
			if (mTriangle[i].x > maxX) maxX = mTriangle[i].x;

			if (mTriangle[i].y < minY) minY = mTriangle[i].y;
			if (mTriangle[i].y > maxY) maxY = mTriangle[i].y;

			if (mTriangle[i].z < minZ) minZ = mTriangle[i].z;
			if (mTriangle[i].z > maxZ) maxZ = mTriangle[i].z;
		}

		mBoundingBox.mMin.x = minX;
		mBoundingBox.mMin.y = minY;
		mBoundingBox.mMin.z = minZ;
		mBoundingBox.mMax.x = maxX;
		mBoundingBox.mMax.y = maxY;
		mBoundingBox.mMax.z = maxZ;
	}

	bool TriangleShape::Intersects(IGeometricShape *other, CollisionData *collision) const
	{
		return false;
	}

	bool TriangleShape::RayIntersects(const Ray &ray, float &t) const
	{
		Triangle translated;
		translated[0] = mTriangle[0] + this->GetPosition();
		translated[1] = mTriangle[1] + this->GetPosition();
		translated[2] = mTriangle[2] + this->GetPosition();

		return ray.GetIntersection(translated, t);
	}
	
	void TriangleShape::DrawDebug(IGraphicsDevice *device, RenderState &state)
	{
		if (!mDebugShape) {
			std::vector<ModelVertex> verts;
			for (int i = 0; i < 3; i++) {
				ModelVertex vert;
				vert.position[0] = mTriangle.GetPoint(i).x;
				vert.position[1] = mTriangle.GetPoint(i).y;
				vert.position[2] = mTriangle.GetPoint(i).z;

				verts.push_back(vert);
			}

			mDebugShape = new Model(verts);
		}

		mDebugShape->SetBlendColor(glm::vec4(1, 0, 0, 1));
		mDebugShape->Render(device, state);
	}
};
