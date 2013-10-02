#pragma once

#include <Engine/Challenge.h>
#include "GeometricShape.h"
#include "PlaneShape.h"
#include <Engine/Math/Ray.h>

namespace challenge
{
	class TriangleShape : public GeometricShape
	{
	public:
		TriangleShape(glm::vec3 a, glm::vec3 b, glm::vec3 c);
		virtual bool Intersects(IGeometricShape *other, CollisionData *collision = NULL) const;

		GeometricShapeType GetType() const { return kShapeTypeTriangle; }

		bool RayIntersects(Ray ray, glm::vec3 *outPoint = NULL) const;

		void SetPoint(int index, const glm::vec3& point)
		{
			mPoints[index] = point;
			this->CalculateNormal();
		}

		const glm::vec3& GetPoint(int i) const { return mPoints[i]; }
		const PlaneShape& GetPlane() const { return mNormalPlane; }
		
	private:
		glm::vec3 mPoints[3];
		PlaneShape mNormalPlane;

		void CalculateNormal()
		{
			glm::vec3 normal = glm::normalize(glm::cross((mPoints[1] - mPoints[0]), (mPoints[2] - mPoints[1])));
			float d = glm::dot(normal, mPoints[0]);
			mNormalPlane = PlaneShape(glm::vec4(normal, d));
		}

		void CalculateBoundingBox();
	};

	typedef std::vector<TriangleShape *> TTriangleList;
};