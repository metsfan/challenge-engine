#pragma once

#include <Challenge/Challenge.h>
#include "GeometricShape.h"
#include <Challenge/Math/Ray.h>
#include <Challenge/Physics/Shapes/Intersection.h>
#include <Challenge/Physics/Shapes/TriangleMeshShape.h>

#define EPSILON 0.001

namespace challenge
{
	class BoxShape : public GeometricShape
	{
	public:
		BoxShape() : GeometricShape() {}
		BoxShape(BoxShape *other);
		BoxShape(const glm::vec3 &dimensions);
		BoxShape(const BoundingBox &box);
		IGeometricShape* Clone() { return new BoxShape(*this); }

		bool RayIntersects(const Ray &ray, float &t) const;

		static IGeometricShape* CreateFromPointsList(const std::vector<glm::vec3> &points, const glm::mat4 &transform);

		GeometricShapeType GetType() const { return kShapeTypeBox; }

		void SetDimensions(const glm::vec3 &dims)
		{
			mDimensions = dims;
			this->UpdateShape();
		}

		void SetHalfX(float halfX)
		{
			mDimensions.x = halfX;
			this->UpdateShape();
		}

		void SetHalfY(float halfY)
		{
			mDimensions.y = halfY;
			this->UpdateShape();
		}

		void SetHalfZ(float halfZ)
		{
			mDimensions.z = halfZ;
			this->UpdateShape();
		}

		const glm::vec3& GetDimensions() const { return mDimensions; }
		real GetHalfX() const { return mDimensions.x; }
		real GetHalfY() const { return mDimensions.y; }
		real GetHalfZ() const { return mDimensions.z; }

		void DrawDebug(IGraphicsDevice *device, RenderState &state);

	private:
		glm::vec3 mDimensions;

		void UpdateShape();
	};
};