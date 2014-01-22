#pragma once

#include <Challenge/Challenge.h>
#include "GeometricShape.h"
#include "PlaneShape.h"
#include <Challenge/Math/Ray.h>
#include <Challenge/Physics/Shapes/Intersection.h>

namespace challenge
{
	class TriangleShape : public GeometricShape
	{
	public:
		TriangleShape(glm::vec3 a, glm::vec3 b, glm::vec3 c);
		virtual bool Intersects(IGeometricShape *other, CollisionData *collision = NULL) const;

		GeometricShapeType GetType() const { return kShapeTypeTriangle; }

		bool RayIntersects(const Ray &ray, float &t) const;

		const glm::vec3& GetPoint(int i) const { return mTriangle.GetPoint(i); }
		const glm::vec4& GetPlane() const { return mTriangle.GetPlane(); }
		const glm::vec3& GetNormal() const { return mTriangle.GetNormal(); }

		void DrawDebug(IGraphicsDevice *device, RenderState &state);

		virtual bool Intersects(const IGeometricShape *other, CollisionData *collision = NULL) const
		{
			return other->Intersects(this, collision);
		}

		virtual bool Intersects(const AABBShape *aabb, CollisionData *collision = NULL) const
		{
			return IntersectionTests::AABBIntersectsTriangle(aabb, this, collision);
		}

		virtual bool Intersects(const OBBShape *obb, CollisionData *collision = NULL) const
		{
			return false;
		}

		virtual bool Intersects(const TriangleShape *triangle, CollisionData *collision = NULL) const
		{
			return false;
		}

		virtual bool Intersects(const TriangleMeshShape *mesh, CollisionData *collision = NULL) const
		{
			return false;
		}
		
	private:
		Triangle mTriangle;

		void CalculateBoundingBox();
	};

	typedef std::vector<TriangleShape *> TTriangleList;
};