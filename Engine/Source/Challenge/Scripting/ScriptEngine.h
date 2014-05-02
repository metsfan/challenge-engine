#pragma once

#include <angelscript/angelscript.h>

#include <Challenge/Challenge.h>
#include <Challenge/Scripting/ScriptFunction.h>

namespace challenge
{
	class ScriptEngine
	{
	public:
		ScriptEngine();
		~ScriptEngine();

		bool LoadFile(const std::string &file);

		asIScriptModule * GetModule() { return mScriptModule; }
		asIScriptContext * GetContext() { return mScriptContext; }
		asIScriptEngine * GetEngine() { return mScriptEngine; }

	private:
		asIScriptEngine *mScriptEngine;
		asIScriptContext *mScriptContext;
		asIScriptModule *mScriptModule;

		static void MessageCallback(const asSMessageInfo *msg, void *param);
		static void Print(std::string &msg);

	};
};


