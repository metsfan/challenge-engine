#include <Challenge/Challenge.h>
#include <Challenge/Scripting/ScriptEngine.h>
#include <Challenge/Util/StaticBlock.h>

#include <angelscript/scriptbuilder/scriptbuilder.h>
#include <angelscript/scriptstdstring/scriptstdstring.h>

namespace challenge
{
	asIScriptEngine *ScriptEngine::mScriptEngine;
	asIScriptContext *ScriptEngine::mScriptContext;
	std::unordered_map<std::string, ScriptModule *> ScriptEngine::mScriptModules;

	StaticBlock staticBlock([]() {
		ScriptEngine::Initialize();
	});

	void ScriptEngine::Initialize()
	{
		mScriptEngine = asCreateScriptEngine(ANGELSCRIPT_VERSION);
		mScriptContext = mScriptEngine->CreateContext();

		mScriptEngine->SetMessageCallback(asFUNCTION(ScriptEngine::MessageCallback), NULL, asCALL_CDECL);

		RegisterStdString(mScriptEngine);

		mScriptEngine->RegisterGlobalFunction("void print(const string &in)", asFUNCTION(ScriptEngine::Print), asCALL_CDECL);
	}

	void ScriptEngine::MessageCallback(const asSMessageInfo *msg, void *param)
	{
		printf("Script Error: %s, Type: %d, Row: %d, Col: %d, Section: %s\n", msg->message, msg->type, msg->row, msg->col, msg->section);
	}

	void ScriptEngine::Print(std::string &msg)
	{
		printf(msg.c_str());
		printf("\n");
	}

	ScriptModule * ScriptEngine::GetModule(const std::string &name)
	{
		auto it = mScriptModules.find(name);
		if (it != mScriptModules.end()) {
			return it->second;
		}

		ScriptModule *newModule = new ScriptModule(name);
		mScriptModules[name] = newModule;

		return newModule;
	}
}

