#pragma once

#include <lua.hpp>
#include <string>

#include "ScriptFunction.h"

class ScriptManager
{
public:
	ScriptManager();
	~ScriptManager();

	bool LoadFile(const std::string &file);

	bool CallFunction(ScriptFunction &function, TScriptParamList &returnValues = TScriptParamList());

private:
	lua_State *mLuaState;
};

