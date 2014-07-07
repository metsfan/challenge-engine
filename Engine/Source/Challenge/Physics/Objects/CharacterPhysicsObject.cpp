#include <Challenge/Challenge.h>
#include <Challenge/Physics/Objects/CharacterPhysicsObject.h>

namespace challenge
{
	CharacterPhysicsObject::CharacterPhysicsObject(IGeometricShape *shape) :
		PhysicsObject(shape),
		mGhostObject(NULL),
		mCharacterController(NULL)
	{
	}

	void CharacterPhysicsObject::ResolveCollision(const CollisionData &collision)
	{
		PhysicsObject::ResolveCollision(collision);

		this->SetVelocity(glm::vec3(0));
	
		glm::vec3 origin = this->GetPosition() + glm::vec3(0, this->GetShape()->GetBoundingBox().GetHeight() * 0.5, 0);
		Ray castRay(origin, glm::vec3(0, -1, 0));
		float t;

		
		if (collision.other->GetPosition().x != 0) {
			int x = 0;
		}
		bool intersects = collision.other->GetShape()->RayIntersects(castRay, t);
		
		if (intersects) {
			

			glm::vec3 rayPos = castRay.ValueAt(t);
			glm::vec3 position = this->GetPosition();
			position.y = rayPos.y + this->GetShape()->GetBoundingBox().GetHeight() * 0.5;
			this->SetPosition(position);
		}
		
	}

	void CharacterPhysicsObject::Update(real seconds)
	{
		btTransform trans = mGhostObject->getWorldTransform();
		mPosition = glm::vec3(trans.getOrigin().x(), trans.getOrigin().y(), trans.getOrigin().z());

		mShape->SetPosition(mPosition);
	}

	void CharacterPhysicsObject::SetPosition(const glm::vec3 &position)
	{
		PhysicsObject::SetPosition(position);

		if (mCharacterController) {
			mCharacterController->warp(ToBullet(mPosition));
		}
	}

	bool CharacterPhysicsObject::CollidesWith(PhysicsObject *other, CollisionData *collision)
	{
		// Cast a ray straight down the y axis into the other object
		return PhysicsObject::CollidesWith(other, collision);
	}

	void CharacterPhysicsObject::SetPhysicsWorld(btDiscreteDynamicsWorld *world)
	{
		btTransform transform(btTransform(btQuaternion(0, 0, 0, 1), ToBullet(mPosition)));
		mMotionState = new btDefaultMotionState(transform);

		mGhostObject = new btPairCachingGhostObject();

		btTransform trans;
		mMotionState->getWorldTransform(trans);
		mGhostObject->setWorldTransform(trans);

		btConvexShape *btShape = dynamic_cast<btConvexShape *>(mShape->GetBulletShape());
		if (!btShape) {
			throw "Character must be a convex shape";
		}

		mGhostObject->setCollisionShape(btShape);
		mGhostObject->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);

		mCharacterController = new btKinematicCharacterController(mGhostObject, btShape, 1);
		world->getPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());

		
		world->addCollisionObject(mGhostObject, btBroadphaseProxy::CharacterFilter, 
			btBroadphaseProxy::StaticFilter | btBroadphaseProxy::DefaultFilter);
		world->addAction(mCharacterController);
		mCharacterController->setWalkDirection(btVector3(0.0, 0.0, 0.0));
		mCharacterController->setMaxSlope(glm::radians(180.0));
		mCharacterController->setUpAxis(1);

		mGhostObject->setUserPointer(this);
	}
}