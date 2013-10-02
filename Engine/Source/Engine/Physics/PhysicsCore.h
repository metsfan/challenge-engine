#pragma once

#include <Engine/Challenge.h>
#include <Engine/Util/Util.h>
#include <Engine/Math/BoundingBox.h>
#include <Engine/Physics/Shapes/GeometricShape.h>

namespace challenge
{
	typedef enum {
		kObjectTypePlane,
		kObjectTypeRigidBody,
		kObjectTypeTriangleMesh
	} PhysicsObjectType;

	class CollisionData;
	class IPhysicsObject;

	typedef void(TCollisionCallback)(IPhysicsObject*, IPhysicsObject*);
	typedef std::vector<TCollisionCallback *> TCollisionCallbackList;

	class IPhysicsObject
	{
	public:
		virtual PhysicsObjectType GetType() = 0;
		virtual std::string GetId() = 0;
		virtual bool CollidesWith(IPhysicsObject *other, CollisionData *collision = NULL) = 0;
		virtual void SetPosition(glm::vec3 position) = 0;
		virtual glm::vec3 GetPosition() = 0;
		virtual IGeometricShape* GetShape() = 0;
		virtual real GetMass() = 0;
		virtual void SetMass(real mass) = 0;
		virtual bool HasInfiniteMass() = 0;
		virtual void AddCollisionCallback(TCollisionCallback callback) = 0;
		virtual void FireCollisionCallbacks(IPhysicsObject *otherObj) = 0;
	};

	class RigidBody;

	typedef std::vector<IPhysicsObject *> TObjectList;
	typedef std::vector<RigidBody *> TRigidBodyList;

	class PhysicsObject : public IPhysicsObject
	{
	public:
		PhysicsObject() { mId = Util::uuid_create(); }

		PhysicsObjectType GetType() { return mType; }
		std::string GetId() { return mId; }

		virtual void SetPosition(glm::vec3 position) { mPosition = position; }
		glm::vec3 GetPosition() { return mPosition; }

		IGeometricShape* GetShape();

		virtual real GetMass() { return mInverseMass; }
		virtual void SetMass(real mass);
		bool HasInfiniteMass() { return mInverseMass <= 0.0f; }

		void AddCollisionCallback(TCollisionCallback callback) { mCollisionCallbacks.push_back(callback); }
		void FireCollisionCallbacks(IPhysicsObject *otherObj);

		PhysicsObjectType mType;
		std::string mId;
		glm::vec3 mPosition;
		IGeometricShape *mShape;
		real mInverseMass;
		real mMass;
		TCollisionCallbackList mCollisionCallbacks;
	};
};