#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Disk/ByteArrayInputStream.h>
#include <Challenge/Disk/ByteArrayOutputStream.h>

namespace challenge
{
	class ISerializable
	{
	public:
		virtual void Serialize(ByteArrayOutputStream &stream) = 0;
		virtual void Unserialize(ByteArrayInputStream &stream) = 0;
	};
}