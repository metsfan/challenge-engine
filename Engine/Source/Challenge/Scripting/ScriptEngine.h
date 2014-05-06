#pragma once

#include <angelscript/angelscript.h>

#include <Challenge/Challenge.h>
#include <Challenge/Scripting/ScriptModule.h>

namespace challenge
{
	class ScriptEngine
	{
		friend class ScriptModule;
		friend class ScriptFunction;

	public:
		//static void Initialize();
		static asIScriptEngine * CreateEngine();

		static asIScriptEngine * GetASEngine() { return mScriptEngine; }
		static ScriptModule * GetModule(const std::string &name);

		static asIScriptContext * CreateContext()
		{
			return mScriptEngine->CreateContext();
		}

	private:
		static asIScriptEngine *mScriptEngine;
		static asIScriptContext *mScriptContext;
		static std::unordered_map<std::string, ScriptModule *> mScriptModules;

		static void MessageCallback(const asSMessageInfo *msg, void *param);
		static void Print(std::string &msg);

		static asIScriptContext * GetContext() { return mScriptContext; }
	};
};


