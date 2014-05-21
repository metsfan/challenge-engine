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

template <typename T, typename... Args>
T f(Args... args)
{
	return T(0);
}


int _tmain(int argc, _TCHAR* argv[])
{
	ScriptEngine engine;

	

	int x = 0, y = 2, z = 3;

	int t = f<int>(x, y, z);

	//engine.LoadFile("scripts/script.as");
	//engine.LoadFile("scripts/vectors.as");
	//engine.LoadFile("scripts/stlvector.as");
	//engine.LoadFile("Scripts/stlmap.as");

	ScriptVector::Register(ScriptEngine::GetASEngine());
	ScriptMap::Register(ScriptEngine::GetASEngine());
	GLMHelper::Register(ScriptEngine::GetASEngine());
	VectorHelper::Register<int>(ScriptEngine::GetASEngine(), "int");
	MapHelper::Register<int, float>(ScriptEngine::GetASEngine(), "int", "float");

	ScriptModule *module = ScriptEngine::GetModule("default1");
	module->AddDefaultScriptsDirectory();
	module->Build();

	//ScriptFunction function("uint64 tester(int)", engine.GetContext(), engine.GetModule());
	//ScriptFunction function("void main(vec2 &in)", engine.GetContext(), engine.GetModule());
	//ScriptFunction function("void main(vector_int &in)", engine.GetContext(), engine.GetModule());
	std::thread thread1([module]() {
		
		ScriptFunction *function = module->GetFunction("float main(map_int_float &in)");
		//function->SetContext(ScriptEngine::CreateContext());

		std::map<int, float> map;
		map[8] = 2.5f;

		float ret = function->Call<float>(&map);

		printf("Return: %f\n", ret);
	});

	std::thread thread2([module]() {
		/*ScriptFunction *function = module->GetFunction("uint64 tester(int x)");
		function->SetContext(ScriptEngine::CreateContext());

		int x = 5;

		uint64_t ret = function->Call<float>(x);

		printf("Return: %lld\n", ret);*/

		ScriptFunction *function = module->GetFunction("float main(map_int_float &in)");
		//function->SetContext(ScriptEngine::CreateContext());

		std::map<int, float> map;
		map[2] = 8.5f;

		float ret = function->Call<float>(&map);

		printf("Return: %f\n", ret);
	});
	

	glm::vec2 testVec(4, 7);
	std::vector<int> vec;
	vec.push_back(3);
	vec.push_back(7);
	vec.push_back(4);

	
	//uint64_t returnValue = function.GetReturnValue<uint64_t>();

	thread1.join();
	thread2.join();

	return 0;
}

