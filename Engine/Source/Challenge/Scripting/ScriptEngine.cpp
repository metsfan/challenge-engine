#include <Challenge/Challenge.h>
#include <Challenge/Scripting/ScriptEngine.h>

#include <angelscript/scriptbuilder/scriptbuilder.h>
#include <angelscript/scriptstdstring/scriptstdstring.h>

namespace challenge
{
	ScriptEngine::ScriptEngine()
	{
		mScriptEngine = asCreateScriptEngine(ANGELSCRIPT_VERSION);
		mScriptContext = mScriptEngine->CreateContext();

		mScriptEngine->SetMessageCallback(asFUNCTION(ScriptEngine::MessageCallback), this, asCALL_CDECL);

		RegisterStdString(mScriptEngine);

		mScriptEngine->RegisterGlobalFunction("void print(const string &in)", asFUNCTION(ScriptEngine::Print), asCALL_CDECL);
	}


	ScriptEngine::~ScriptEngine()
	{
		mScriptContext->Release();
		mScriptEngine->Release();
	}

	bool ScriptEngine::LoadFile(const std::string &file)
	{
		int result;

		CScriptBuilder builder;
		
		result = builder.StartNewModule(mScriptEngine, "module");

		result = builder.AddSectionFromFile(file.c_str());

		result = builder.BuildModule();

		mScriptModule = mScriptEngine->GetModule("module");

		return true;
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
}

