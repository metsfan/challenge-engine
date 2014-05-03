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

		template <typename T, typename U>
		static void RegisterMatrixFunctions(asIScriptEngine *engine, const std::string &main, const std::string &sub);

		/* Basic Operators */
		template <typename T, typename U> static void opAddAssign(asIScriptGeneric *gen);
		template <typename T, typename U> static void opSubAssign(asIScriptGeneric *gen);
		template <typename T, typename U> static void opMulAssign(asIScriptGeneric *gen);
		template <typename T, typename U> static void opDivAssign(asIScriptGeneric *gen);
		template <typename T, typename U> static void opAdd(asIScriptGeneric *gen);
		template <typename T, typename U> static void opSub(asIScriptGeneric *gen);
		template <typename T, typename U> static void opMul(asIScriptGeneric *gen);
		template <typename T, typename U> static void opDiv(asIScriptGeneric *gen);
		template <typename T> static void opIndex(asIScriptGeneric *gen);
		template <typename T> static void opAssign(asIScriptGeneric *gen);

		/* Matrix-Vector operators */
		template <typename T, typename U> static void opMulVecAssign(asIScriptGeneric *gen);
		template <typename T, typename U> static void opDivVecAssign(asIScriptGeneric *gen);
		template <typename T, typename U> static void opMulVec(asIScriptGeneric *gen);
		template <typename T, typename U> static void opDivVec(asIScriptGeneric *gen);

		/* Vector math functions */
		template <typename T, typename U> static void dot(asIScriptGeneric *gen);
		template <typename T, typename U> static void length(asIScriptGeneric *gen);
		template <typename T, typename U> static void length2(asIScriptGeneric *gen);
		template <typename T> static void cross(asIScriptGeneric *gen);
		template <typename T> static void min(asIScriptGeneric *gen);
		template <typename T> static void max(asIScriptGeneric *gen);
		template <typename T> static void normalize(asIScriptGeneric *gen);

		/* Matrix functions */
		template <typename T, typename U> static void rotate(asIScriptGeneric *gen);
		template <typename T, typename U> static void translate(asIScriptGeneric *gen);
		template <typename T, typename U> static void scale(asIScriptGeneric *gen);
		template <typename T, typename U> static void determinant(asIScriptGeneric *gen);
		template <typename T> static void inverse(asIScriptGeneric *gen);
		template <typename T> static void transpose(asIScriptGeneric *gen);
	};
};

#include <Challenge/Scripting/Helpers/GLMHelper.inl>