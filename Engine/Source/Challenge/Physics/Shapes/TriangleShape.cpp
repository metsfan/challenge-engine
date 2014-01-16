#include <Challenge/Challenge.h>
//#include <Challenge/Physics/Shapes/Intersection.h>
#include "TriangleShape.h"

namespace challenge
{
	TriangleShape::TriangleShape(glm::vec3 a, glm::vec3 b, glm::vec3 c)
	{
		mPoints[0] = a;
		mPoints[1] = b;
		mPoints[2] = c;

		this->CalculateNormal();
		this->CalculateBoundingBox();
	}

	void TriangleShape::CalculateBoundingBox()
	{
		float minX, minY, minZ, maxX, maxY, maxZ;
		minX = minY = minZ = INFINITY;
		maxX = maxY = maxZ = -INFINITY;

		for(int i = 0; i < 3; i++) {
			if(mPoints[i].x < minX) minX = mPoints[i].x;
			if(mPoints[i].x > maxX) maxX = mPoints[i].x;

			if(mPoints[i].y < minY) minY = mPoints[i].y;
			if(mPoints[i].y > maxY) maxY = mPoints[i].y;

			if(mPoints[i].z < minZ) minZ = mPoints[i].z;
			if(mPoints[i].z > maxZ) maxZ = mPoints[i].z;
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

	bool TriangleShape::RayIntersects(Ray ray, glm::vec3 *outPoint) const
	{
		/*glm::vec4 L = glm::vec4(mNormalPlane.mNormal, glm::dot(-mNormalPlane.mNormal, mPoints[0]));
		glm::vec4 S = glm::vec4(ray.origin, 1.0);
		glm::vec4 V = glm::vec4(ray.direction, 1.0);

		real LDotV = glm::dot(L, V);
		if(LDotV == 0) {
			return false;
		}

		real LDotS = glm::dot(L, S);

		real t = LDotS / LDotV;

		glm::vec3 P = ray.ValueAt(t);

		glm::vec3 R = P - mPoints[0];
		glm::vec3 Q1 = mPoints[1] - mPoints[0];
		glm::vec3 Q2 = mPoints[2] - mPoints[0];

		real RDotQ1 = glm::dot(R, Q1);
		real RDotQ2 = glm::dot(R, Q2);
		real Q1DotQ2 = glm::dot(Q1, Q2);
		real Q1DotQ1 = glm::dot(Q1, Q1);
		real Q2DotQ2 = glm::dot(Q2, Q2);

		glm::vec2 barys = glm::inverse(glm::mat2(Q1DotQ1, Q1DotQ2, Q1DotQ2, Q2DotQ2)) * glm::vec2(RDotQ1, RDotQ2);

		if(barys.x + barys.y < 1) {
			real w0 = 1.0 - barys.x - barys.y;
			real w1 = barys.x;
			real w2 = barys.y;

			outPoint[0] = (w0 * mPoints[0]) + (w1 * mPoints[1]) + (w2 * mPoints[2]);

			return true;
		}
		*/
		return false;
	}
};
