#pragma once

#include <string>
#include <vector>

#include "ScriptParamHolder.h"

typedef std::vector<ScriptParamHolder> TScriptParamList;

class ScriptFunction
{
public:
	ScriptFunction(const std::string &name, int numRetValues) :
		mName(name),
		mNumRetValues(numRetValues)
	{
	}

	~ScriptFunction()
	{
	}

	const std::string& GetName() { return mName; }

	void PushIntParameter(int value)
	{
		mParams.resize(mParams.size() + 1);

		ScriptParamHolder &param = mParams.back();
		param.SetIntValue(value);
	}

	void PushBoolParameter(bool value)
	{
		mParams.resize(mParams.size() + 1);

		ScriptParamHolder &param = mParams.back();
		param.SetBoolValue(value);
	}

	void PushNumberParameter(double value)
	{
		mParams.resize(mParams.size() + 1);

		ScriptParamHolder &param = mParams.back();
		param.SetNumberValue(value);
	}

	void PushStringParameter(const char *value)
	{
		mParams.resize(mParams.size() + 1);

		ScriptParamHolder &param = mParams.back();
		param.SetStringValue(value);
	}

	void PushFunctionParameter(lua_CFunction value)
	{
		mParams.resize(mParams.size() + 1);

		ScriptParamHolder &param = mParams.back();
		param.SetFunctionValue(value);
	}

	void PushUserdataParameter(void *value)
	{
		mParams.resize(mParams.size() + 1);

		ScriptParamHolder &param = mParams.back();
		param.SetUserdataValue(value);
	}

	const std::vector<ScriptParamHolder>& GetParams() { return mParams; }

	bool Execute(lua_State *state, TScriptParamList &returnValues);

private:
	std::string mName;
	int mNumRetValues;
	std::vector<ScriptParamHolder> mParams;
};

