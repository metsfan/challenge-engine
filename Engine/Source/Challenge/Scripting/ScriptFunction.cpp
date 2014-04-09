#include "stdafx.h"
#include "ScriptFunction.h"

bool ScriptFunction::Execute(lua_State *state, TScriptParamList &returnValues)
{
	lua_getglobal(state, mName.c_str());

	for (auto &param : mParams) {
		switch (param.GetType())
		{
		case ScriptParamTypeBool:
			lua_pushboolean(state, param.GetBoolValue());
			break;

		case ScriptParamTypeInteger:
			lua_pushinteger(state, param.GetIntValue());
			break;

		case ScriptParamTypeNumber:
			lua_pushnumber(state, param.GetNumberValue());
			break;

		case ScriptParamTypeString:
			lua_pushstring(state, param.GetStringValue());
			break;

		case ScriptParamTypeFunction:
			lua_pushcfunction(state, param.GetFunctionValue());
			break;

		case ScriptParamTypeUserdata:
			lua_pushlightuserdata(state, param.GetUserdataValue());
			break;
		}
	}

	int result = lua_pcall(state, mParams.size(), mNumRetValues, NULL);
	if (result != LUA_OK) {
		return false;
	}

	if (mNumRetValues > 0) {
		returnValues.resize(mNumRetValues);

		for (int i = 1; i <= mNumRetValues; i++) {
			ScriptParamHolder &param = returnValues[i-1];

			//LUA_TNIL, LUA_TNUMBER, LUA_TBOOLEAN, LUA_TSTRING, LUA_TTABLE, LUA_TFUNCTION, LUA_TUSERDATA, LUA_TTHREAD, and LUA_TLIGHTUSERDATA.

			int type = lua_type(state, i);
			switch (type)
			{
			case LUA_TNIL:
				param.SetNilValue();
				break;

			case LUA_TNUMBER:
				param.SetNumberValue(lua_tonumber(state, i));
				break;

			case LUA_TBOOLEAN:
				param.SetBoolValue(lua_toboolean(state, i));
				break;

			case LUA_TSTRING:
				param.SetStringValue(lua_tostring(state, i));
				break;

			case LUA_TFUNCTION:
				param.SetFunctionValue(lua_tocfunction(state, i));
				break;

			case LUA_TUSERDATA:
				param.SetUserdataValue(lua_touserdata(state, i));
				break;
			}
		}
	}

	return true;
}
