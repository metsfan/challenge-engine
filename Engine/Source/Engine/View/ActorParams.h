#pragma once

#include <Engine/Challenge.h>

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