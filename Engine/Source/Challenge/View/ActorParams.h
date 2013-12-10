#pragma once

#include <Challenge/Challenge.h>

namespace challenge
{
	struct ActorParams
	{
		ActorId mId;
		ActorType mType;

		ActorParams();
		virtual ~ActorParams();
	};
};