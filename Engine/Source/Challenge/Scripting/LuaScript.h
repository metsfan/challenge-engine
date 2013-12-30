#pragma once

#include <Challenge/Challenge.h>
#include <lua/lua.hpp>

namespace challenge
{
	class LuaScript
	{
	public:
		LuaScript();
		LuaScript(File *file);
		LuaScript(const std::string &code);
		~LuaScript();

	private:
		lua_State *mState;
	};
};