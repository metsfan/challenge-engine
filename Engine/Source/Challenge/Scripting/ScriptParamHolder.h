#pragma once

#include <lua.hpp>

enum ScriptParamType
{
	ScriptParamTypeNil,
	ScriptParamTypeBool,
	ScriptParamTypeInteger,
	ScriptParamTypeNumber,
	ScriptParamTypeString,
	ScriptParamTypeFunction,
	ScriptParamTypeUserdata,
	ScriptParamTypeThread,
	ScriptParamTypeTable
};

class ScriptParamHolder
{
public:
	ScriptParamHolder()
	{
	}

	~ScriptParamHolder()
	{
	}

	void SetNilValue() { mType = ScriptParamTypeNil; }
	void SetIntValue(int value) { mIntValue = value; mType = ScriptParamTypeInteger; }
	void SetBoolValue(bool value) { mBoolValue = value; mType = ScriptParamTypeBool; }
	void SetNumberValue(double value) { mNumberValue = value; mType = ScriptParamTypeNumber; }
	void SetStringValue(const char *value) { mStringValue = value; mType = ScriptParamTypeString; }
	void SetFunctionValue(lua_CFunction value) { mFunctionValue = value; mType = ScriptParamTypeFunction; }
	void SetUserdataValue(void *value) { mUserdataValue = value; mType = ScriptParamTypeUserdata; }

	int GetIntValue() const { return mIntValue; }
	bool GetBoolValue() const { return mBoolValue; }
	double GetNumberValue() const { return mNumberValue; }
	const char * GetStringValue() const { return mStringValue; }
	lua_CFunction GetFunctionValue() const { return mFunctionValue; }
	void * GetUserdataValue() const { return mUserdataValue; }

	ScriptParamType GetType() const { return mType; }

private:
	int mIntValue;
	bool mBoolValue;
	double mNumberValue;
	const char *mStringValue;
	lua_CFunction mFunctionValue;
	void *mUserdataValue;

	ScriptParamType mType;
};

