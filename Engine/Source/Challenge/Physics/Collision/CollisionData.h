#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Physics/Collision/Contact.h>

namespace challenge
{
	typedef std::vector<Contact *> TContactList;

	class CollisionData
	{
	public:
		CollisionData();

		void CalculateInternals(real duration);

		TContactList mContacts;
	};
};