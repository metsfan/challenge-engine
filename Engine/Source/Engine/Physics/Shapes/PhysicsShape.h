#pragma once

#include <Engine/Challenge.h>
#include <Engine/Physics/BoundingBox.h>
#include <Engine/Physics/Collision/CollisionData.h>

namespace challenge
{
	typedef enum {
		kShapeTypeAABB,
		kShapeTypePlane,
		kShapeTypeSphere,
		kShapeTypeTriangle,
		kShapeTypeTriangleMesh,
		kShapeTypeConcaveTriangleMesh
	} PhysicsShapeType;

	typedef std::vector<Point> TPointsList;
	class IPhysicsShape
	{
	public:
		virtual bool Intersects(IPhysicsShape *other, CollisionData *collision = NULL) = 0;
		//virtual TPointsList Intersection(IPhysicsShape *other) = 0;

		virtual PhysicsShapeType GetType() = 0;
		virtual glm::vec3 GetPosition() = 0;
		virtual void SetPosition(glm::vec3 position) = 0;
		virtual glm::mat3 CalculateInertiaTensor(float mass) = 0;
		virtual BoundingBox GetBoundingBox() = 0;
	};

	typedef std::list<IPhysicsShape *> TPhysicsShapeLinkedList;

	class PhysicsShape : public IPhysicsShape
	{
	public:
		virtual bool Intersects(IPhysicsShape *other, CollisionData *collision = NULL) = 0;
		//virtual TPointsList Intersection(IPhysicsShape *other) = 0;

		virtual PhysicsShapeType GetType() = 0;
		virtual glm::vec3 GetPosition() { return mPosition; }
		virtual void SetPosition(glm::vec3 position) { mPosition = position; }
		virtual glm::mat3 CalculateInertiaTensor(float mass) { return glm::mat3(); }
		virtual BoundingBox GetBoundingBox() { return mBoundingBox; }

	protected:
		glm::vec3 mPosition;
		BoundingBox mBoundingBox;
	};
};