#pragma once

#include <Challenge/Challenge.h>

#include <angelscript/angelscript.h>

namespace challenge
{
	class ScriptObject
	{
	public:
		ScriptObject();
		~ScriptObject();

		//void Register(ScriptEngine *engine);

	protected:
		virtual void RegisterObject(asIScriptEngine *engine) = 0;
	};
};