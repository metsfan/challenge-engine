#pragma once

#include <Challenge/Challenge.h>

namespace challenge
{
	class VectorHelper
	{
	public:
		template <typename T>
		static void Register(asIScriptEngine *engine, const std::string &typeName, std::string vectorName = "");
	};
};

#include <Challenge/Scripting/Helpers/VectorHelper.inl>