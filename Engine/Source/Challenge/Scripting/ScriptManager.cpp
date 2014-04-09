#include "stdafx.h"
#include "ScriptManager.h"


ScriptManager::ScriptManager()
{
	mLuaState = luaL_newstate();

	luaL_openlibs(mLuaState);
}


ScriptManager::~ScriptManager()
{
	lua_close(mLuaState);
}

bool ScriptManager::LoadFile(const std::string &file)
{
	int result = luaL_loadfile(mLuaState, file.c_str());
	if (result != LUA_OK) {
		return false;
	}

	result = lua_pcall(mLuaState, 0, 0, 0);
	if (result != LUA_OK) {
		return false;
	}
	
	return true;
}

bool ScriptManager::CallFunction(ScriptFunction &function, TScriptParamList &returnValues)
{
	return function.Execute(mLuaState, returnValues);
}
