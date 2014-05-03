#pragma once

#include <Challenge/Challenge.h>
#include <angelscript/angelscript.h>

namespace challenge
{
	enum GLMOperators
	{
		GLMOpAddAssign = (1 << 1),
		GLMOpSubAssign = (1 << 2), 
		GLMOpMulAssign = (1 << 3),
		GLMOpDivAssign = (1 << 4),
		GLMOpAdd = (1 << 5),
		GLMOpSub = (1 << 6),
		GLMOpMul = (1 << 7),
		GLMOpDiv = (1 << 8),
		GLMOpIndex = (1 << 9)
	};

	static const int GLMOpAllButIndex = 0x000000FF;

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
		template <typename T, typename U>
		static void RegisterOperators(asIScriptEngine *engine, const std::string &main, const std::string &sub,
			uint32_t flags = 0xFFFFFFFF);

		template <typename T, typename U>
		static void RegisterMatVecOperators(asIScriptEngine *engine, const std::string &main, const std::string &sub,
			uint32_t flags = 0xFFFFFFFF);

		template <typename T, typename U>
		static void RegisterVecMathFunctions(asIScriptEngine *engine, const std::string &main, const std::string &sub);
	};
};

#include <Challenge/Scripting/Helpers/GLMHelper.inl>