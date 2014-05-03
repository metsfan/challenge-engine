// Scripting.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Challenge/Challenge.h>
#include <Challenge/Scripting/ScriptEngine.h>
#include <Challenge/Scripting/ScriptFunction.h>
#include <Challenge/Scripting/Types/ScriptVector.h>
#include <Challenge/Scripting/Types/ScriptMap.h>
#include <Challenge/Scripting/Helpers/GLMHelper.h>
#include <Challenge/Scripting/Helpers/VectorHelper.h>
#include <Challenge/Scripting/Helpers/MapHelper.h>

#include <angelscript/angelscript.h>

using namespace challenge;

int _tmain(int argc, _TCHAR* argv[])
{
	ScriptEngine engine;

	ScriptVector::Register(engine.GetEngine());
	ScriptMap::Register(engine.GetEngine());
	GLMHelper::Register(engine.GetEngine());
	VectorHelper::Register<int>(engine.GetEngine(), "int");
	MapHelper::Register<int, float>(engine.GetEngine(), "int", "float");

	//engine.LoadFile("scripts/script.as");
	//engine.LoadFile("scripts/vectors.as");
	//engine.LoadFile("scripts/stlvector.as");
	engine.LoadFile("scripts/stlmap.as");

	//ScriptFunction function("uint64 tester(int)", engine.GetContext(), engine.GetModule());
	//ScriptFunction function("void main(vec2 &in)", engine.GetContext(), engine.GetModule());
	//ScriptFunction function("void main(vector_int &in)", engine.GetContext(), engine.GetModule());
	ScriptFunction function("void main(map_int_float &in)", engine.GetContext(), engine.GetModule());

	glm::vec2 testVec(4, 7);
	std::vector<int> vec;
	vec.push_back(3);
	vec.push_back(7);
	vec.push_back(4);

	std::map<int, float> map;
	map[8] = 2.5f;

	//function.Call(&testVec);
	//function.Call(&vec);
	function.Call(&map);
	//uint64_t returnValue = function.GetReturnValue<uint64_t>();

	return 0;
}

