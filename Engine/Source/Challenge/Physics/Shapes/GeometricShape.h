#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Math/BoundingBox.h>
#include <Challenge/Physics/Collision/CollisionData.h>
#include <Challenge/Math/Ray.h>
#include <Challenge/Renderer/Shape/MeshShape.h>


namespace challenge
{
	typedef enum {
		kShapeTypeAABB,
		kShapeTypeOBB,
		kShapeTypePlane,
		kShapeTypeSphere,
		kShapeTypeTriangle,
		kShapeTypeTriangleMesh
	} GeometricShapeType;

	struct DebugLinesVertex
	{
		float position[3];
		float color[4];
	};

	typedef std::vector<Point> TPointsList;

	class Model;

	class AABBShape;
	class OBBShape;
	class TriangleShape;
	class TriangleMeshShape;

	class IGeometricShape
	{
	public:
		virtual bool Intersects(const IGeometricShape *other, CollisionData *collision = NULL) const = 0;
		virtual bool Intersects(const BoundingBox &bounds) const = 0;

		virtual bool Intersects(const AABBShape *aabb, CollisionData *collision = NULL) const = 0;
		virtual bool Intersects(const OBBShape *obb, CollisionData *collision = NULL) const = 0;
		virtual bool Intersects(const TriangleShape *triangle, CollisionData *collision = NULL) const = 0;
		virtual bool Intersects(const TriangleMeshShape *mesh, CollisionData *collision = NULL) const = 0;
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

		virtual void DrawDebug(IGraphicsDevice *device, RenderState &state) = 0;
	};

	typedef std::list<IGeometricShape *> TGeometricShapeLinkedList;

	class GeometricShape : public IGeometricShape
	{
	public:
		GeometricShape();
		GeometricShape(GeometricShape *other);
		virtual ~GeometricShape();
		
		virtual bool Intersects(const BoundingBox &bounds) const { return mBoundingBox.Intersects(bounds); }
		virtual bool Contains(const BoundingBox &bounds) const { return mBoundingBox.Contains(bounds); }
		virtual bool ContainedWithin(const BoundingBox &bounds) const { return bounds.Contains(mBoundingBox); }
		//virtual TPointsList Intersection(IGeometricShape *other) = 0;

		virtual glm::vec3 GetPosition() const { return mPosition; }
		virtual void SetPosition(glm::vec3 position) 
		{ 
			mPosition = position; 
			this->CalculateBoundingBox();
		}

		virtual glm::mat3 CalculateInertiaTensor(float mass) { return glm::mat3(); }
		virtual BoundingBox GetBoundingBox() const { return mBoundingBox; }

		virtual IGeometricShape* Clone() { return NULL; }
		virtual void SetTransform(const glm::mat4 &transform) { mTransform = transform; }

		bool RayIntersects(const Ray &ray, float &t) const { return false; }

		virtual void DrawDebug(IGraphicsDevice *device, RenderState &state) {}

	protected:
		glm::vec3 mPosition;
		BoundingBox mBoundingBox;
		glm::mat4 mTransform;
		Model *mDebugShape;

	private:
		virtual void CalculateBoundingBox() {}

	};
};

#include <Challenge/Physics/Shapes/AABBShape.h>
#include <Challenge/Physics/Shapes/TriangleMeshShape.h>
#include <Challenge/Physics/Shapes/OBBShape.h>
#include <Challenge/Physics/Shapes/PlaneShape.h>
#include <Challenge/Physics/Shapes/SphereShape.h>
#include <Challenge/Physics/Shapes/TriangleMeshShape.h>
#include <Challenge/Physics/Shapes/TriangleShape.h>

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

			case kShapeTypeOBB:
				return OBBShape::CreateFromPointsList(points, transform);

			case kShapeTypeTriangleMesh:
				return TriangleMeshShape::CreateFromPointsList(points);
				break;
			}
		}
	};
};