#pragma once

#include <Challenge/Challenge.h>
//#include <Challenge/Physics/Collision/Contact.h>

namespace challenge
{
	//typedef std::vector<Contact *> TContactList;

	struct CollisionData
	{
		real penetrationDepth = 0;
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