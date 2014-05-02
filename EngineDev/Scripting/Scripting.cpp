// Scripting.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Challenge/Challenge.h>
#include <Challenge/Scripting/ScriptEngine.h>
#include <Challenge/Scripting/ScriptFunction.h>
#include <Challenge/Scripting/Types/ScriptVector.h>
#include <Challenge/Scripting/Types/ScriptMap.h>
#include <Challenge/Scripting/Helpers/GLMHelper.h>

#include <angelscript/angelscript.h>

using namespace challenge;

int _tmain(int argc, _TCHAR* argv[])
{
	ScriptEngine engine;

	ScriptVector::Register(engine.GetEngine());
	ScriptMap::Register(engine.GetEngine());
	GLMHelper::Register(engine.GetEngine());

	//engine.LoadFile("scripts/script.as");
	engine.LoadFile("scripts/vectors.as");

	//ScriptFunction function("uint64 tester(int)", engine.GetContext(), engine.GetModule());
	ScriptFunction function("void main(vec2 &in)", engine.GetContext(), engine.GetModule());

	glm::vec2 testVec(4, 7);

	function.Call(&testVec);
	//uint64_t returnValue = function.GetReturnValue<uint64_t>();

	return 0;
}

