#pragma once

#include <Challenge/Challenge.h>
#include <angelscript/angelscript.h>

namespace challenge
{
	class GLMHelper
	{
	public:
		static void Register(asIScriptEngine *engine);

		static void RegisterVec2(asIScriptEngine *engine);
		static void RegisterVec3(asIScriptEngine *engine);
		static void RegisterVec4(asIScriptEngine *engine);
		static void RegisterMat2(asIScriptEngine *engine);
		static void RegisterMat3(asIScriptEngine *engine);
		static void RegisterMat4(asIScriptEngine *engine);

	private:
		template <typename T>
		static void opAddAssign(asIScriptGeneric *gen)
		{
			T &obj = *(T *) gen->GetObjectA();
			float arg= gen->GetArgFloat(0);
			obj += arg;
			gen->SetReturnObject(&obj);
		}

		template <typename T>
		static void opSubAssign(asIScriptGeneric *gen)
		{
			T &obj = *(T *) gen->GetObjectA();
			float arg = gen->GetArgFloat(0);
			obj -= arg;
			gen->SetReturnObject(&obj);
		}

		template <typename T>
		static void opMulAssign(asIScriptGeneric *gen)
		{
			T &obj = *(T *) gen->GetObjectA();
			float arg = gen->GetArgFloat(0);
			obj *= arg;
			gen->SetReturnObject(&obj);
		}

		template <typename T>
		static void opDivAssign(asIScriptGeneric *gen)
		{
			T &obj = *(T *) gen->GetObjectA();
			float arg = gen->GetArgFloat(0);
			obj /= arg;
			gen->SetReturnObject(&obj);
		}

		template <typename T>
		static void opAdd(asIScriptGeneric *gen)
		{
			T &obj = *(T *) gen->GetObjectA();
			float arg = gen->GetArgFloat(0);
			T outVec = obj + arg;
			gen->SetReturnObject(&outVec);
		}

		template <typename T>
		static void opSub(asIScriptGeneric *gen)
		{
			T &obj = *(T *) gen->GetObjectA();
			float arg = gen->GetArgFloat(0);
			T outVec = obj - arg;
			gen->SetReturnObject(&outVec);
		}

		template <typename T>
		static void opMul(asIScriptGeneric *gen)
		{
			T &obj = *(T *) gen->GetObjectA();
			float arg = gen->GetArgFloat(0);
			T outVec = obj * arg;
			gen->SetReturnObject(&outVec);
		}

		template <typename T>
		static void opDiv(asIScriptGeneric *gen)
		{
			T &obj = *(T *) gen->GetObjectA();
			float arg = gen->GetArgFloat(0);
			T outVec = obj / arg;
			gen->SetReturnObject(&outVec);
		}

		template <typename T>
		static void opIndex(asIScriptGeneric *gen)
		{
			T &obj = *(T *) gen->GetObjectA();
			int arg = gen->GetArgDWord(0);
			gen->SetReturnFloat(obj[arg]);
		}
	};
};