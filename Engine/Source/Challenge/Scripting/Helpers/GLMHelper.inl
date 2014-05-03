#include <Challenge/Scripting/Helpers/GLMHelper.h>
#include <Challenge/Scripting/Helpers/ScriptBasics.h>

#include <glm/gtx/norm.hpp>

#include <angelscript/angelscript.h>

namespace challenge
{
	void GLMHelper::Register(asIScriptEngine *engine)
	{
		RegisterVec2(engine);
		RegisterVec3(engine);
		RegisterVec4(engine);

		RegisterMat2(engine);
		RegisterMat3(engine);
		RegisterMat4(engine);
	}

	void GLMHelper::RegisterVec2(asIScriptEngine *engine)
	{
		engine->RegisterObjectType("vec2", sizeof(glm::vec2), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS);
		engine->RegisterObjectBehaviour("vec2", asBEHAVE_CONSTRUCT, "void f(float, float)",
			asFUNCTION((ScriptBasics::ConstructEx<glm::vec2, float, float>)), asCALL_CDECL_OBJFIRST);

		engine->RegisterObjectProperty("vec2", "float x", asOFFSET(glm::vec2, x));
		engine->RegisterObjectProperty("vec2", "float y", asOFFSET(glm::vec2, y));

		engine->RegisterObjectProperty("vec2", "float r", asOFFSET(glm::vec2, r));
		engine->RegisterObjectProperty("vec2", "float g", asOFFSET(glm::vec2, g));

		engine->RegisterObjectProperty("vec2", "float s", asOFFSET(glm::vec2, s));
		engine->RegisterObjectProperty("vec2", "float t", asOFFSET(glm::vec2, t));

		RegisterOperators<glm::vec2, float>(engine, "vec2", "float");
		RegisterOperators<glm::vec2, glm::vec2>(engine, "vec2", "vec2", GLMOpAllButIndex);

		RegisterVecMathFunctions<glm::vec2, float>(engine, "vec2", "float");
	}

	void GLMHelper::RegisterVec3(asIScriptEngine *engine)
	{
		engine->RegisterObjectType("vec3", sizeof(glm::vec3), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS);
		engine->RegisterObjectBehaviour("vec3", asBEHAVE_CONSTRUCT, "void f(float, float, float)", 
			asFUNCTION((ScriptBasics::ConstructEx<glm::vec3, float, float, float>)), asCALL_CDECL_OBJFIRST);

		engine->RegisterObjectProperty("vec3", "float x", asOFFSET(glm::vec3, x));
		engine->RegisterObjectProperty("vec3", "float y", asOFFSET(glm::vec3, y));
		engine->RegisterObjectProperty("vec3", "float z", asOFFSET(glm::vec3, z));

		engine->RegisterObjectProperty("vec3", "float r", asOFFSET(glm::vec3, r));
		engine->RegisterObjectProperty("vec3", "float g", asOFFSET(glm::vec3, g));
		engine->RegisterObjectProperty("vec3", "float b", asOFFSET(glm::vec3, b));

		engine->RegisterObjectProperty("vec3", "float s", asOFFSET(glm::vec3, s));
		engine->RegisterObjectProperty("vec3", "float t", asOFFSET(glm::vec3, t));
		engine->RegisterObjectProperty("vec3", "float p", asOFFSET(glm::vec3, p));

		RegisterOperators<glm::vec3, float>(engine, "vec3", "float");
		RegisterOperators<glm::vec3, glm::vec3>(engine, "vec3", "vec3", GLMOpAllButIndex);

		RegisterVecMathFunctions<glm::vec3, float>(engine, "vec3", "float");
		engine->RegisterGlobalFunction("vec3 cross(vec3 &in, vec3 &in)", asFUNCTION(GLMHelper::cross<glm::vec3>), asCALL_GENERIC);
	}

	void GLMHelper::RegisterVec4(asIScriptEngine *engine)
	{
		engine->RegisterObjectType("vec4", sizeof(glm::vec4), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS);
		engine->RegisterObjectBehaviour("vec4", asBEHAVE_CONSTRUCT, "void f(float, float, float, float)",
			asFUNCTION((ScriptBasics::ConstructEx<glm::vec4, float, float, float, float>)), asCALL_CDECL_OBJFIRST);

		engine->RegisterObjectProperty("vec4", "float x", asOFFSET(glm::vec4, x));
		engine->RegisterObjectProperty("vec4", "float y", asOFFSET(glm::vec4, y));
		engine->RegisterObjectProperty("vec4", "float z", asOFFSET(glm::vec4, z));
		engine->RegisterObjectProperty("vec4", "float w", asOFFSET(glm::vec4, w));

		engine->RegisterObjectProperty("vec4", "float r", asOFFSET(glm::vec4, r));
		engine->RegisterObjectProperty("vec4", "float g", asOFFSET(glm::vec4, g));
		engine->RegisterObjectProperty("vec4", "float b", asOFFSET(glm::vec4, b));
		engine->RegisterObjectProperty("vec4", "float a", asOFFSET(glm::vec4, a));

		engine->RegisterObjectProperty("vec4", "float s", asOFFSET(glm::vec4, s));
		engine->RegisterObjectProperty("vec4", "float t", asOFFSET(glm::vec4, t));
		engine->RegisterObjectProperty("vec4", "float p", asOFFSET(glm::vec4, p));
		engine->RegisterObjectProperty("vec4", "float q", asOFFSET(glm::vec4, q));

		RegisterOperators<glm::vec4, float>(engine, "vec4", "float");
		RegisterOperators<glm::vec4, glm::vec4>(engine, "vec4", "vec4", GLMOpAllButIndex);

		RegisterVecMathFunctions<glm::vec4, float>(engine, "vec4", "float");
	}

	void GLMHelper::RegisterMat2(asIScriptEngine *engine)
	{
		engine->RegisterObjectType("mat2", sizeof(glm::mat2), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS);
		engine->RegisterObjectBehaviour("mat2", asBEHAVE_CONSTRUCT, "void f(vec2 &in, vec2 &in)",
			asFUNCTION((ScriptBasics::ConstructEx<glm::mat2, glm::vec2, glm::vec2>)), asCALL_CDECL_OBJFIRST);
		engine->RegisterObjectBehaviour("mat2", asBEHAVE_CONSTRUCT, "void f(float, float, float, float)",
			asFUNCTION((ScriptBasics::ConstructEx<glm::mat2, float, float, float, float>)), asCALL_CDECL_OBJFIRST);
		
		RegisterOperators<glm::mat2, float>(engine, "mat2", "float", GLMOpAllButIndex);
		RegisterMatVecOperators<glm::mat2, glm::vec2>(engine, "mat2", "vec2");
		RegisterOperators<glm::mat2, glm::mat2>(engine, "mat2", "mat2", GLMOpAllButIndex);

		engine->RegisterGlobalFunction("float determinant(mat2 &in)",
			asFUNCTION((GLMHelper::determinant<glm::mat2, float>)), asCALL_GENERIC);
		engine->RegisterGlobalFunction("mat2 inverse(mat2 &in)",
			asFUNCTION((GLMHelper::inverse<glm::mat2>)), asCALL_GENERIC);
		engine->RegisterGlobalFunction("mat2 transpose(mat2 &in)",
			asFUNCTION((GLMHelper::transpose<glm::mat2>)), asCALL_GENERIC);
	}

	void GLMHelper::RegisterMat3(asIScriptEngine *engine)
	{
		engine->RegisterObjectType("mat3", sizeof(glm::mat2), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS);
		engine->RegisterObjectBehaviour("mat3", asBEHAVE_CONSTRUCT, "void f(vec3 &in, vec3 &in, vec3 &in)",
			asFUNCTION((ScriptBasics::ConstructEx<glm::mat3, glm::vec3, glm::vec3, glm::vec3>)), asCALL_CDECL_OBJFIRST);
		engine->RegisterObjectBehaviour("mat3", asBEHAVE_CONSTRUCT, "void f(float, float, float, float, float, float, float, float, float)",
			asFUNCTION((ScriptBasics::ConstructEx<glm::mat3, float, float, float, float, 
			float, float, float, float, float>)), asCALL_CDECL_OBJFIRST);
	
		RegisterOperators<glm::mat3, float>(engine, "mat3", "float", GLMOpAllButIndex);
		RegisterMatVecOperators<glm::mat3, glm::vec3>(engine, "mat3", "vec3");
		RegisterOperators<glm::mat3, glm::mat3>(engine, "mat3", "mat3", GLMOpAllButIndex);

		engine->RegisterGlobalFunction("float determinant(mat3 &in)",
			asFUNCTION((GLMHelper::determinant<glm::mat3, float>)), asCALL_GENERIC);
		engine->RegisterGlobalFunction("mat3 inverse(mat3 &in)",
			asFUNCTION((GLMHelper::inverse<glm::mat3>)), asCALL_GENERIC);
		engine->RegisterGlobalFunction("mat3 transpose(mat3 &in)",
			asFUNCTION((GLMHelper::transpose<glm::mat3>)), asCALL_GENERIC);
	}

	void GLMHelper::RegisterMat4(asIScriptEngine *engine)
	{
		engine->RegisterObjectType("mat4", sizeof(glm::mat2), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS);
		engine->RegisterObjectBehaviour("mat4", asBEHAVE_CONSTRUCT, "void f(vec4 &in, vec4 &in, vec4 &in, vec4 &in)",
			asFUNCTION((ScriptBasics::ConstructEx<glm::mat4, glm::vec4, glm::vec4, glm::vec4, glm::vec4>)), asCALL_CDECL_OBJFIRST);
		engine->RegisterObjectBehaviour("mat4", asBEHAVE_CONSTRUCT, "void f(float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float)",
			asFUNCTION((ScriptBasics::ConstructEx<glm::mat4, float, float, float, float,
			float, float, float, float, float, float, float, float, float, float, float, float>)), asCALL_CDECL_OBJFIRST);

		RegisterOperators<glm::mat4, float>(engine, "mat4", "float", GLMOpAllButIndex);
		RegisterMatVecOperators<glm::mat4, glm::vec4>(engine, "mat4", "vec4");
		RegisterOperators<glm::mat4, glm::mat4>(engine, "mat4", "mat4", GLMOpAllButIndex);

		engine->RegisterGlobalFunction("mat4 rotate(mat4 &in, float, float, float, float)",
			asFUNCTION((GLMHelper::rotate<glm::mat4, float>)), asCALL_GENERIC);
		engine->RegisterGlobalFunction("mat4 scale(mat4 &in, float, float, float)",
			asFUNCTION((GLMHelper::scale<glm::mat4, float>)), asCALL_GENERIC);
		engine->RegisterGlobalFunction("mat4 translate(mat4 &in, float, float, float)",
			asFUNCTION((GLMHelper::translate<glm::mat4, float>)), asCALL_GENERIC);
		engine->RegisterGlobalFunction("float determinant(mat4 &in)",
			asFUNCTION((GLMHelper::determinant<glm::mat4, float>)), asCALL_GENERIC);
		engine->RegisterGlobalFunction("mat4 inverse(mat4 &in)",
			asFUNCTION((GLMHelper::inverse<glm::mat4>)), asCALL_GENERIC);
		engine->RegisterGlobalFunction("mat4 transpose(mat4 &in)",
			asFUNCTION((GLMHelper::transpose<glm::mat4>)), asCALL_GENERIC);
	}

	template <typename T, typename U>
	void GLMHelper::RegisterOperators(asIScriptEngine *engine, const std::string &main, const std::string &sub, uint32_t flags)
	{
		std::string fn;

		if (flags & GLMOpAddAssign) {
			fn = main + " opAddAssign(" + sub + " &in)";
			engine->RegisterObjectMethod(main.c_str(), fn.c_str(), asFUNCTION((GLMHelper::opAddAssign<T, U>)), asCALL_GENERIC);
		}

		if (flags & GLMOpSubAssign) {
			fn = main + " opSubAssign(" + sub + " &in)";
			engine->RegisterObjectMethod(main.c_str(), fn.c_str(), asFUNCTION((GLMHelper::opSubAssign<T, U>)), asCALL_GENERIC);
		}

		if (flags & GLMOpMulAssign) {
			fn = main + " opMulAssign(" + sub + " &in)";
			engine->RegisterObjectMethod(main.c_str(), fn.c_str(), asFUNCTION((GLMHelper::opMulAssign<T, U>)), asCALL_GENERIC);
		}

		if (flags & GLMOpDivAssign) {
			fn = main + " opDivAssign(" + sub + " &in)";
			engine->RegisterObjectMethod(main.c_str(), fn.c_str(), asFUNCTION((GLMHelper::opDivAssign<T, U>)), asCALL_GENERIC);
		}

		if (flags & GLMOpAdd) {
			fn = main + " opAdd(" + sub + " &in)";
			engine->RegisterObjectMethod(main.c_str(), fn.c_str(), asFUNCTION((GLMHelper::opAdd<T, U>)), asCALL_GENERIC);
		}

		if (flags & GLMOpSub) {
			fn = main + " opSub(" + sub + " &in)";
			engine->RegisterObjectMethod(main.c_str(), fn.c_str(), asFUNCTION((GLMHelper::opSub<T, U>)), asCALL_GENERIC);
		}

		if (flags & GLMOpMul) {
			fn = main + " opMul(" + sub + " &in)";
			engine->RegisterObjectMethod(main.c_str(), fn.c_str(), asFUNCTION((GLMHelper::opMul<T, U>)), asCALL_GENERIC);
		}

		if (flags & GLMOpDiv) {
			fn = main + " opDiv(" + sub + " &in)";
			engine->RegisterObjectMethod(main.c_str(), fn.c_str(), asFUNCTION((GLMHelper::opDiv<T, U>)), asCALL_GENERIC);
		}

		if (flags & GLMOpIndex) {
			fn = sub + " opIndex(int)";
			engine->RegisterObjectMethod(main.c_str(), fn.c_str(), asFUNCTION(GLMHelper::opIndex<T>), asCALL_GENERIC);
		}

	}

	template <typename T, typename U>
	void GLMHelper::RegisterMatVecOperators(asIScriptEngine *engine, const std::string &main, const std::string &sub, uint32_t flags)
	{
		std::string fn;

		if (flags & GLMOpMulAssign) {
			fn = main + " opMulAssign(" + sub + " &in)";
			engine->RegisterObjectMethod(main.c_str(), fn.c_str(), asFUNCTION((GLMHelper::opMulVecAssign<T, U>)), asCALL_GENERIC);
		}

		if (flags & GLMOpDivAssign) {
			fn = main + " opDivAssign(" + sub + " &in)";
			engine->RegisterObjectMethod(main.c_str(), fn.c_str(), asFUNCTION((GLMHelper::opDivVecAssign<T, U>)), asCALL_GENERIC);
		}

		if (flags & GLMOpMul) {
			fn = sub + " opMul(" + sub + " &in)";
			engine->RegisterObjectMethod(main.c_str(), fn.c_str(), asFUNCTION((GLMHelper::opMulVec<T, U>)), asCALL_GENERIC);
		}

		if (flags & GLMOpDiv) {
			fn = sub + " opDiv(" + sub + " &in)";
			engine->RegisterObjectMethod(main.c_str(), fn.c_str(), asFUNCTION((GLMHelper::opDivVec<T, U>)), asCALL_GENERIC);
		}

		if (flags & GLMOpIndex) {
			fn = sub + " opIndex(int)";
			engine->RegisterObjectMethod(main.c_str(), fn.c_str(), asFUNCTION(GLMHelper::opIndex<T>), asCALL_GENERIC);
		}

	}

	template <typename T, typename U>
	static void GLMHelper::RegisterVecMathFunctions(asIScriptEngine *engine, const std::string &main, const std::string &sub)
	{
		std::string fn;

		fn = sub + " dot(" + main + " &in, " + main + " &in)";
		engine->RegisterGlobalFunction(fn.c_str(), asFUNCTION((GLMHelper::dot<T, U>)), asCALL_GENERIC);

		fn = sub + " length(" + main + " &in)";
		engine->RegisterGlobalFunction(fn.c_str(), asFUNCTION((GLMHelper::length<T, U>)), asCALL_GENERIC);

		fn = sub + " length2(" + main + " &in)";
		engine->RegisterGlobalFunction(fn.c_str(), asFUNCTION((GLMHelper::length2<T, U>)), asCALL_GENERIC);

		fn = main + " min(" + main + " &in, " + main + " &in)";
		engine->RegisterGlobalFunction(fn.c_str(), asFUNCTION(GLMHelper::min<T>), asCALL_GENERIC);

		fn = main + " max(" + main + " &in, " + main + " &in)";
		engine->RegisterGlobalFunction(fn.c_str(), asFUNCTION(GLMHelper::max<T>), asCALL_GENERIC);

		fn = main + " normalize(" + main + " &in)";
		engine->RegisterGlobalFunction(fn.c_str(), asFUNCTION(GLMHelper::normalize<T>), asCALL_GENERIC);
	}

	/* Basic Operators */

	template <typename T, typename U>
	void GLMHelper::opAddAssign(asIScriptGeneric *gen)
	{
		T &obj = *(T *) gen->GetObject();
		U &arg = *(U *) gen->GetAddressOfArg(0);
		obj += arg;
		gen->SetReturnObject(&obj);
	}

	template <typename T, typename U>
	void GLMHelper::opSubAssign(asIScriptGeneric *gen)
	{
		T &obj = *(T *) gen->GetObject();
		U &arg = *(U *) gen->GetAddressOfArg(0);
		obj -= arg;
		gen->SetReturnObject(&obj);
	}

	template <typename T, typename U>
	void GLMHelper::opMulAssign(asIScriptGeneric *gen)
	{
		T &obj = *(T *) gen->GetObject();
		U &arg = *(U *) gen->GetAddressOfArg(0);
		obj *= arg;
		gen->SetReturnObject(&obj);
	}

	template <typename T, typename U>
	void GLMHelper::opDivAssign(asIScriptGeneric *gen)
	{
		T &obj = *(T *) gen->GetObject();
		U &arg = *(U *) gen->GetAddressOfArg(0);
		obj /= arg;
		gen->SetReturnObject(&obj);
	}

	template <typename T, typename U>
	void GLMHelper::opAdd(asIScriptGeneric *gen)
	{
		T &obj = *(T *) gen->GetObject();
		U &arg = *(U *) gen->GetAddressOfArg(0);
		T outObj = obj + arg;
		gen->SetReturnObject(&outObj);
	}

	template <typename T, typename U>
	void GLMHelper::opSub(asIScriptGeneric *gen)
	{
		T &obj = *(T *) gen->GetObject();
		U &arg = *(U *) gen->GetAddressOfArg(0);
		T outObj = obj - arg;
		gen->SetReturnObject(&outObj);
	}

	template <typename T, typename U>
	void GLMHelper::opMul(asIScriptGeneric *gen)
	{
		T &obj = *(T *) gen->GetObject();
		U &arg = *(U *) gen->GetAddressOfArg(0);
		T outObj = obj * arg;
		gen->SetReturnObject(&outObj);
	}

	template <typename T, typename U>
	void GLMHelper::opDiv(asIScriptGeneric *gen)
	{
		T &obj = *(T *) gen->GetObject();
		U &arg = *(U *) gen->GetAddressOfArg(0);
		T outObj = obj / arg;
		gen->SetReturnObject(&outObj);
	}

	template <typename T>
	void GLMHelper::opIndex(asIScriptGeneric *gen)
	{
		T &obj = *(T *) gen->GetObject();
		int arg = gen->GetArgDWord(0);
		gen->SetReturnAddress(&obj[arg]);
	}

	template <typename T> 
	void GLMHelper::opAssign(asIScriptGeneric *gen)
	{
		T &obj = *(T *) gen->GetObject();
		T &arg = *(T *) gen->GetArgObject(0);
		gen->SetReturnAddress(&arg);
	}

	/* Matrix-Vector operators */

	template <typename T, typename U>
	void GLMHelper::opMulVecAssign(asIScriptGeneric *gen)
	{
		T &obj = *(T *) gen->GetObject();
		U &arg = *(U *) gen->GetAddressOfArg(0);
		obj *= arg;
		gen->SetReturnObject(&obj);
	}

	template <typename T, typename U>
	void GLMHelper::opDivVecAssign(asIScriptGeneric *gen)
	{
		T &obj = *(T *) gen->GetObject();
		U &arg = *(U *) gen->GetAddressOfArg(0);
		obj /= arg;
		gen->SetReturnObject(&obj);
	}

	template <typename T, typename U>
	void GLMHelper::opMulVec(asIScriptGeneric *gen)
	{
		T &obj = *(T *) gen->GetObject();
		U &arg = *(U *) gen->GetAddressOfArg(0);
		U outObj = obj * arg;
		gen->SetReturnObject(&outObj);
	}

	template <typename T, typename U>
	void GLMHelper::opDivVec(asIScriptGeneric *gen)
	{
		T &obj = *(T *) gen->GetObject();
		U &arg = *(U *) gen->GetAddressOfArg(0);
		U outObj = obj / arg;
		gen->SetReturnObject(&outObj);
	}

	/* Vector math functions */
	template <typename T, typename U> 
	void GLMHelper::dot(asIScriptGeneric *gen)
	{
		T &arg1 = *(T *) gen->GetArgObject(0);
		T &arg2 = *(T *) gen->GetArgObject(1);

		U &result = *(U *) gen->GetAddressOfReturnLocation();
		result = glm::dot(arg1, arg2);

		gen->SetReturnAddress(&result);
	}

	template <typename T, typename U> 
	void GLMHelper::length(asIScriptGeneric *gen)
	{
		T &arg1 = *(T *) gen->GetArgObject(0);

		U &result = *(U *) gen->GetAddressOfReturnLocation();
		result = glm::length(arg1);

		gen->SetReturnAddress(&result);
	}

	template <typename T, typename U> 
	void GLMHelper::length2(asIScriptGeneric *gen)
	{
		T &arg1 = *(T *) gen->GetArgObject(0);

		U &result = *(U *) gen->GetAddressOfReturnLocation();
		result = glm::length2(arg1);

		gen->SetReturnAddress(&result);
	}

	template <typename T> 
	void GLMHelper::cross(asIScriptGeneric *gen)
	{
		T &arg1 = *(T *) gen->GetArgObject(0);
		T &arg2 = *(T *) gen->GetArgObject(1);

		T &outArg = *(T *) gen->GetAddressOfReturnLocation();

		outArg = glm::cross(arg1, arg2);
		gen->SetReturnAddress(&outArg);
	}

	template <typename T> 
	void GLMHelper::min(asIScriptGeneric *gen)
	{
		T &arg1 = *(T *) gen->GetArgObject(0);
		T &arg2 = *(T *) gen->GetArgObject(1);

		T &outArg = *(T *) gen->GetAddressOfReturnLocation();

		outArg = glm::min(arg1, arg2);
		gen->SetReturnAddress(&outArg);
	}

	template <typename T> 
	void GLMHelper::max(asIScriptGeneric *gen)
	{
		T &arg1 = *(T *) gen->GetArgObject(0);
		T &arg2 = *(T *) gen->GetArgObject(1);

		T &outArg = *(T *) gen->GetAddressOfReturnLocation();

		outArg = glm::max(arg1, arg2);
		gen->SetReturnAddress(&outArg);
	}

	template <typename T>
	void GLMHelper::normalize(asIScriptGeneric *gen)
	{
		T &arg1 = *(T *) gen->GetArgObject(0);

		T &outArg = *(T *) gen->GetAddressOfReturnLocation();

		outArg = glm::normalize(arg1);
		gen->SetReturnAddress(&outArg);
	}

	/* Matrix functions */
	template <typename T, typename U> 
	void GLMHelper::rotate(asIScriptGeneric *gen)
	{
		T &mat = *(T *) gen->GetAddressOfArg(0);
		U &angle = *(U *) gen->GetAddressOfArg(1);
		U &x = *(U *) gen->GetAddressOfArg(2);
		U &y = *(U *) gen->GetAddressOfArg(3);
		U &z = *(U *) gen->GetAddressOfArg(4);

		T &outMat = *(T *) gen->GetAddressOfReturnLocation();
		outMat = glm::rotate(mat, angle, x, y, z);

		gen->SetReturnAddress(&outMat);
	}

	template <typename T, typename U> 
	void GLMHelper::translate(asIScriptGeneric *gen)
	{
		T &mat = *(T *) gen->GetAddressOfArg(0);
		U &x = *(U *) gen->GetAddressOfArg(1);
		U &y = *(U *) gen->GetAddressOfArg(2);
		U &z = *(U *) gen->GetAddressOfArg(3);

		T &outMat = *(T *) gen->GetAddressOfReturnLocation();
		outMat = glm::translate(mat, x, y, z);

		gen->SetReturnAddress(&outMat);
	}

	template <typename T, typename U> 
	void GLMHelper::scale(asIScriptGeneric *gen)
	{
		T &mat = *(T *) gen->GetAddressOfArg(0);
		U &x = *(U *) gen->GetAddressOfArg(1);
		U &y = *(U *) gen->GetAddressOfArg(2);
		U &z = *(U *) gen->GetAddressOfArg(3);

		T &outMat = *(T *) gen->GetAddressOfReturnLocation();
		outMat = glm::scale(mat, x, y, z);

		gen->SetReturnAddress(&outMat);
	}

	template <typename T, typename U> 
	void GLMHelper::determinant(asIScriptGeneric *gen)
	{
		T &mat = *(T *) gen->GetAddressOfArg(0);

		U &outVal = *(U *) gen->GetAddressOfReturnLocation();
		outVal = glm::determinant(mat);

		gen->SetReturnAddress(&outVal);
	}

	template <typename T> 
	void GLMHelper::inverse(asIScriptGeneric *gen)
	{
		T &mat = *(T *) gen->GetAddressOfArg(0);

		T &outMat = *(T *) gen->GetAddressOfReturnLocation();
		outMat = glm::inverse(mat);

		gen->SetReturnAddress(&outMat);
	}

	template <typename T> 
	void GLMHelper::transpose(asIScriptGeneric *gen)
	{
		T &mat = *(T *) gen->GetAddressOfArg(0);

		T &outMat = *(T *) gen->GetAddressOfReturnLocation();
		outMat = glm::transpose(mat);

		gen->SetReturnAddress(&outMat);
	}
}