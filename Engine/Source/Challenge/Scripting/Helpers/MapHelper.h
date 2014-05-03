#pragma once

#include <Challenge/Challenge.h>
#include <angelscript/angelscript.h>

namespace challenge
{
	class MapHelper
	{
	public:
		template <typename K, typename V>
		static void Register(asIScriptEngine *engine, const std::string &keyName, const std::string &valueName, std::string mapName = "");
	};
};

#include <Challenge/Scripting/Helpers/MapHelper.inl>