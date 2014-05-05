#include <Challenge/Challenge.h>
#include <Challenge/Scripting/ScriptFunction.h>

namespace challenge
{
	ScriptFunction::ScriptFunction(ScriptModule *module, const std::string &signature) :
		mContext(ScriptEngine::GetContext())
	{
		if (!module || !module->GetModule()) {
			throw "Module is not initialized";
		}

		mFunction = module->GetModule()->GetFunctionByDecl(signature.c_str());
		mFunction->AddRef();
	}

	ScriptFunction::~ScriptFunction()
	{
		mFunction->Release();
	}
}