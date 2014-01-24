#pragma once

#include <Challenge/Challenge.h>
//#include <Challenge/Physics/Collision/Contact.h>

namespace challenge
{
	//typedef std::vector<Contact *> TContactList;

	class PhysicsObject;

	struct CollisionData
	{
		PhysicsObject *other = NULL;
		glm::vec3 penetrationDepth;
		glm::vec3 collisionNormal;
	};

	/*class CollisionData
	{
	public:
		CollisionData()
		{
		}

		~CollisionData()
		{
		}

		void SetPenetrationDepth(real depth)
		{
			mPenetrationDepth = depth;
		}

		real GetPenetrationDepth() { return mPenetrationDepth; }

	private:
		real mPenetrationDepth;
	};*/
};