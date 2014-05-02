#include <Challenge/Challenge.h>
#include <Challenge/Scripting/ScriptFunction.h>

namespace challenge
{
	ScriptFunction::ScriptFunction(const std::string &signature, asIScriptContext *context, asIScriptModule *module) :
		mContext(context)
	{
		mFunction = module->GetFunctionByDecl(signature.c_str());
		mFunction->AddRef();
	}

	ScriptFunction::~ScriptFunction()
	{
		mFunction->Release();
	}
}
