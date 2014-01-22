#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Physics/Shapes/GeometricShape.h>

namespace challenge
{
	class OBBShape : public GeometricShape
	{
	public:
		OBBShape() : GeometricShape() {}
		OBBShape(const glm::vec3 &center, const glm::vec3 &dimensions, const glm::mat3 &axes);
		OBBShape(const BoundingBox &box, const glm::mat3 &axes);
		OBBShape(OBBShape *other);
		virtual ~OBBShape() {}
		IGeometricShape* Clone() { return new OBBShape(*this); }

		virtual bool Intersects(const IGeometricShape *other, CollisionData *collision = NULL) const
		{
			return other->Intersects(this, collision);
		}

		virtual bool Intersects(const AABBShape *aabb, CollisionData *collision = NULL) const
		{
			return IntersectionTests::AABBIntersectsOBB(aabb, this, collision);
		}

		virtual bool Intersects(const OBBShape *obb, CollisionData *collision = NULL) const
		{
			return IntersectionTests::OBBIntersectsOBB(this, obb, collision);
		}

		virtual bool Intersects(const TriangleShape *triangle, CollisionData *collision = NULL) const
		{
			return false;
		}

		virtual bool Intersects(const TriangleMeshShape *mesh, CollisionData *collision = NULL) const
		{
			return false;
		}

		bool RayIntersects(const Ray &ray, float &t) const;

		static IGeometricShape* CreateFromPointsList(const std::vector<glm::vec3> &points, const glm::mat4 &transform);

		GeometricShapeType GetType() const { return kShapeTypeOBB; }
		glm::vec3 GetPosition() const { return mCenter + mPosition; }

		void SetDimensions(const glm::vec3 &dims)
		{
			mDimensions = dims;
			this->CalculateBoundingBox();
		}

		void SetHalfX(float halfX)
		{
			mDimensions.x = halfX;
			this->CalculateBoundingBox();
		}

		void SetHalfY(float halfY)
		{
			mDimensions.y = halfY;
			this->CalculateBoundingBox();
		}

		void SetHalfZ(float halfZ)
		{
			mDimensions.z = halfZ;
			this->CalculateBoundingBox();
		}

		const glm::vec3& GetDimensions() const { return mDimensions; }
		real GetHalfX() const { return mDimensions.x; }
		real GetHalfY() const { return mDimensions.y; }
		real GetHalfZ() const { return mDimensions.z; }

		void SetCenter(const glm::vec3 &center)
		{
			mCenter = center;
			this->CalculateBoundingBox();
		}

		void SetX(real x)
		{
			mCenter.x = x;
			this->CalculateBoundingBox();
		}

		void SetY(real y)
		{
			mCenter.y = y;
			this->CalculateBoundingBox();
		}

		void SetZ(real z)
		{
			mCenter.z = z;
			this->CalculateBoundingBox();
		}

		const glm::vec3& GetCenter() const { return mCenter; }
		real GetX() const { return mCenter.x; }
		real GetY() const { return mCenter.y; }
		real GetZ() const { return mCenter.z; }

		const glm::mat3& GetAxes() const { return mAxes; }
		void SetAxes(const glm::mat3 &axes) { mAxes = axes; }

		virtual void SetTransform(const glm::mat4 &transform);

		void DrawDebug(IGraphicsDevice *device, RenderState &state);

	private:
		glm::vec3 mCenter;
		glm::vec3 mBaseCenter;
		glm::vec3 mDimensions;
		glm::vec3 mBaseDimensions;
		glm::mat3 mAxes;

		void CalculateBoundingBox()
		{
			mBoundingBox.mMin.x = mPosition.x + mCenter.x - mDimensions.x;
			mBoundingBox.mMin.y = mPosition.y + mCenter.y - mDimensions.y;
			mBoundingBox.mMin.z = mPosition.z + mCenter.z - mDimensions.z;
			mBoundingBox.mMax.x = mPosition.x + mCenter.x + mDimensions.x;
			mBoundingBox.mMax.y = mPosition.y + mCenter.y + mDimensions.y;
			mBoundingBox.mMax.z = mPosition.z + mCenter.z + mDimensions.z;
		}
	};
};