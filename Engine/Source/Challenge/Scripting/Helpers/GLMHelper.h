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

	private:
		template <typename vecType>
		static void opAddAssign(asIScriptGeneric *gen)
		{
			vecType &vector = *(vecType *) gen->GetObjectA();
			float arg= gen->GetArgFloat(0);
			vector += arg;
			gen->SetReturnObject(&vector);
		}

		template <typename vecType>
		static void opSubAssign(asIScriptGeneric *gen)
		{
			vecType &vector = *(vecType *) gen->GetObjectA();
			float arg = gen->GetArgFloat(0);
			vector -= arg;
			gen->SetReturnObject(&vector);
		}

		template <typename vecType>
		static void opMulAssign(asIScriptGeneric *gen)
		{
			vecType &vector = *(vecType *) gen->GetObjectA();
			float arg = gen->GetArgFloat(0);
			vector *= arg;
			gen->SetReturnObject(&vector);
		}

		template <typename vecType>
		static void opDivAssign(asIScriptGeneric *gen)
		{
			vecType &vector = *(vecType *) gen->GetObjectA();
			float arg = gen->GetArgFloat(0);
			vector /= arg;
			gen->SetReturnObject(&vector);
		}

		template <typename vecType>
		static void opAdd(asIScriptGeneric *gen)
		{
			vecType &vector = *(vecType *) gen->GetObjectA();
			float arg = gen->GetArgFloat(0);
			vecType outVec = vector + arg;
			gen->SetReturnObject(&outVec);
		}

		template <typename vecType>
		static void opSub(asIScriptGeneric *gen)
		{
			vecType &vector = *(vecType *) gen->GetObjectA();
			float arg = gen->GetArgFloat(0);
			vecType outVec = vector - arg;
			gen->SetReturnObject(&outVec);
		}

		template <typename vecType>
		static void opMul(asIScriptGeneric *gen)
		{
			vecType &vector = *(vecType *) gen->GetObjectA();
			float arg = gen->GetArgFloat(0);
			vecType outVec = vector * arg;
			gen->SetReturnObject(&outVec);
		}

		template <typename vecType>
		static void opDiv(asIScriptGeneric *gen)
		{
			vecType &vector = *(vecType *) gen->GetObjectA();
			float arg = gen->GetArgFloat(0);
			vecType outVec = vector / arg;
			gen->SetReturnObject(&outVec);
		}

		template <typename vecType>
		static void opIndex(asIScriptGeneric *gen)
		{
			vecType &vector = *(vecType *) gen->GetObjectA();
			int arg = gen->GetArgDWord(0);
			gen->SetReturnFloat(vector[arg]);
		}
	};
};