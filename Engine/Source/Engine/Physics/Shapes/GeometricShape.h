#pragma once

#include <Engine/Challenge.h>
#include <Engine/Math/BoundingBox.h>
#include <Engine/Physics/Collision/CollisionData.h>
#include <Engine/Math/Ray.h>

namespace challenge
{
	typedef enum {
		kShapeTypeAABB,
		kShapeTypePlane,
		kShapeTypeSphere,
		kShapeTypeTriangle,
		kShapeTypeTriangleMesh,
		kShapeTypeConcaveTriangleMesh
	} GeometricShapeType;

	typedef std::vector<Point> TPointsList;

	class IGeometricShape
	{
	public:
		virtual bool Intersects(IGeometricShape *other, CollisionData *collision = NULL) const = 0;
		virtual bool Intersects(const BoundingBox &bounds) const = 0;
		//virtual TPointsList Intersection(IGeometricShape *other) = 0;

		virtual GeometricShapeType GetType() const = 0;
		virtual glm::vec3 GetPosition() const = 0;
		virtual void SetPosition(glm::vec3 position) = 0;
		virtual glm::mat3 CalculateInertiaTensor(float mass) = 0;
		virtual BoundingBox GetBoundingBox() const = 0;
		virtual IGeometricShape* Clone() = 0;
		virtual void SetTransform(const glm::mat4 &transform) = 0;
		virtual bool RayIntersects(const Ray &ray, float &t) const = 0;
		virtual bool Contains(const BoundingBox &bounds) const = 0;
		virtual bool ContainedWithin(const BoundingBox &bounds) const = 0;
	};

	typedef std::list<IGeometricShape *> TGeometricShapeLinkedList;

	class GeometricShape : public IGeometricShape
	{
	public:
		GeometricShape() {}
		GeometricShape(GeometricShape *other);
		
		virtual bool Intersects(const BoundingBox &bounds) const { return mBoundingBox.Intersects(bounds); }
		virtual bool Contains(const BoundingBox &bounds) const { return mBoundingBox.Contains(bounds); }
		virtual bool ContainedWithin(const BoundingBox &bounds) const { return bounds.Contains(mBoundingBox); }
		//virtual TPointsList Intersection(IGeometricShape *other) = 0;

		virtual glm::vec3 GetPosition() const { return mPosition; }
		virtual void SetPosition(glm::vec3 position) { mPosition = position; }
		virtual glm::mat3 CalculateInertiaTensor(float mass) { return glm::mat3(); }
		virtual BoundingBox GetBoundingBox() const { return mBoundingBox; }

		virtual IGeometricShape* Clone() { return NULL; }
		virtual void SetTransform(const glm::mat4 &transform) { mTransform = transform; }

		bool RayIntersects(const Ray &ray, float &t) const { return false; }

	protected:
		glm::vec3 mPosition;
		BoundingBox mBoundingBox;
		glm::mat4 mTransform;

	private:
		void CalculateBoundingBox() {}

	};
};

#include <Engine/Physics/Shapes/AABBShape.h>
#include <Engine/Physics/Shapes/ConcaveTriangleMeshShape.h>
#include <Engine/Physics/Shapes/PlaneShape.h>
#include <Engine/Physics/Shapes/SphereShape.h>
#include <Engine/Physics/Shapes/TriangleMeshShape.h>
#include <Engine/Physics/Shapes/TriangleShape.h>

namespace challenge
{
	class GeometricShapeFactory
	{
	public:
		static IGeometricShape* CreateFromPointsList(GeometricShapeType type, const std::vector<glm::vec3> &points, const glm::mat4 &transform)
		{
			switch(type)
			{
			case kShapeTypeAABB:
				return AABBShape::CreateFromPointsList(points, transform);

			case kShapeTypeTriangleMesh:
				//return TriangleMeshShape::CreateFromPointsList(points);
				break;

			case kShapeTypeConcaveTriangleMesh:
				//return ConcaveTriangleMeshShape::CreateFromPointsList(points, transform);
				break;
			}
		}
	};
};