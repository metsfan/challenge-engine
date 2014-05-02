#include <Challenge/Challenge.h>
#include <Challenge/Scripting/Helpers/GLMHelper.h>

namespace challenge
{
	void GLMHelper::Register(asIScriptEngine *engine)
	{
		RegisterVec2(engine);
		RegisterVec3(engine);
		RegisterVec4(engine);
	}

	void GLMHelper::RegisterVec2(asIScriptEngine *engine)
	{
		engine->RegisterObjectType("vec2", sizeof(glm::vec2), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS);

		engine->RegisterObjectProperty("vec2", "float x", asOFFSET(glm::vec2, x));
		engine->RegisterObjectProperty("vec2", "float y", asOFFSET(glm::vec2, y));

		engine->RegisterObjectProperty("vec2", "float r", asOFFSET(glm::vec2, r));
		engine->RegisterObjectProperty("vec2", "float g", asOFFSET(glm::vec2, g));

		engine->RegisterObjectProperty("vec2", "float s", asOFFSET(glm::vec2, s));
		engine->RegisterObjectProperty("vec2", "float t", asOFFSET(glm::vec2, t));

		engine->RegisterObjectMethod("vec2", "vec2 opAddAssign(float)", asFUNCTION(GLMHelper::opAddAssign<glm::vec2>), asCALL_GENERIC);
		engine->RegisterObjectMethod("vec2", "vec2 opSubAssign(float)", asFUNCTION(GLMHelper::opSubAssign<glm::vec2>), asCALL_GENERIC);
		engine->RegisterObjectMethod("vec2", "vec2 opMulAssign(float)", asFUNCTION(GLMHelper::opMulAssign<glm::vec2>), asCALL_GENERIC);
		engine->RegisterObjectMethod("vec2", "vec2 opDivAssign(float)", asFUNCTION(GLMHelper::opDivAssign<glm::vec2>), asCALL_GENERIC);
		engine->RegisterObjectMethod("vec2", "vec2 opAdd(float)", asFUNCTION(GLMHelper::opAdd<glm::vec2>), asCALL_GENERIC);
		engine->RegisterObjectMethod("vec2", "vec2 opSub(float)", asFUNCTION(GLMHelper::opSub<glm::vec2>), asCALL_GENERIC);
		engine->RegisterObjectMethod("vec2", "vec2 opMul(float)", asFUNCTION(GLMHelper::opMul<glm::vec2>), asCALL_GENERIC);
		engine->RegisterObjectMethod("vec2", "vec2 opDiv(float)", asFUNCTION(GLMHelper::opDiv<glm::vec2>), asCALL_GENERIC);

		engine->RegisterObjectMethod("vec2", "float opIndex(int)", asFUNCTION(GLMHelper::opIndex<glm::vec2>), asCALL_GENERIC);
	}

	void GLMHelper::RegisterVec3(asIScriptEngine *engine)
	{
		engine->RegisterObjectType("vec3", sizeof(glm::vec2), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS);

		engine->RegisterObjectProperty("vec3", "float x", asOFFSET(glm::vec3, x));
		engine->RegisterObjectProperty("vec3", "float y", asOFFSET(glm::vec3, y));
		engine->RegisterObjectProperty("vec3", "float z", asOFFSET(glm::vec3, z));

		engine->RegisterObjectProperty("vec3", "float r", asOFFSET(glm::vec3, r));
		engine->RegisterObjectProperty("vec3", "float g", asOFFSET(glm::vec3, g));
		engine->RegisterObjectProperty("vec3", "float b", asOFFSET(glm::vec3, b));

		engine->RegisterObjectProperty("vec3", "float s", asOFFSET(glm::vec3, s));
		engine->RegisterObjectProperty("vec3", "float t", asOFFSET(glm::vec3, t));
		engine->RegisterObjectProperty("vec3", "float p", asOFFSET(glm::vec3, p));

		engine->RegisterObjectMethod("vec3", "vec3 opAddAssign(float)", asFUNCTION(GLMHelper::opAddAssign<glm::vec3>), asCALL_GENERIC);
		engine->RegisterObjectMethod("vec3", "vec3 opSubAssign(float)", asFUNCTION(GLMHelper::opSubAssign<glm::vec3>), asCALL_GENERIC);
		engine->RegisterObjectMethod("vec3", "vec3 opMulAssign(float)", asFUNCTION(GLMHelper::opMulAssign<glm::vec3>), asCALL_GENERIC);
		engine->RegisterObjectMethod("vec3", "vec3 opDivAssign(float)", asFUNCTION(GLMHelper::opDivAssign<glm::vec3>), asCALL_GENERIC);
		engine->RegisterObjectMethod("vec3", "vec3 opAdd(float)", asFUNCTION(GLMHelper::opAdd<glm::vec3>), asCALL_GENERIC);
		engine->RegisterObjectMethod("vec3", "vec3 opSub(float)", asFUNCTION(GLMHelper::opSub<glm::vec3>), asCALL_GENERIC);
		engine->RegisterObjectMethod("vec3", "vec3 opMul(float)", asFUNCTION(GLMHelper::opMul<glm::vec3>), asCALL_GENERIC);
		engine->RegisterObjectMethod("vec3", "vec3 opDiv(float)", asFUNCTION(GLMHelper::opDiv<glm::vec3>), asCALL_GENERIC);

		engine->RegisterObjectMethod("vec3", "float opIndex(int)", asFUNCTION(GLMHelper::opIndex<glm::vec3>), asCALL_GENERIC);
	}

	void GLMHelper::RegisterVec4(asIScriptEngine *engine)
	{
		engine->RegisterObjectType("vec4", sizeof(glm::vec2), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS);

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

		engine->RegisterObjectMethod("vec4", "vec4 opAddAssign(float)", asFUNCTION(GLMHelper::opAddAssign<glm::vec4>), asCALL_GENERIC);
		engine->RegisterObjectMethod("vec4", "vec4 opSubAssign(float)", asFUNCTION(GLMHelper::opSubAssign<glm::vec4>), asCALL_GENERIC);
		engine->RegisterObjectMethod("vec4", "vec4 opMulAssign(float)", asFUNCTION(GLMHelper::opMulAssign<glm::vec4>), asCALL_GENERIC);
		engine->RegisterObjectMethod("vec4", "vec4 opDivAssign(float)", asFUNCTION(GLMHelper::opDivAssign<glm::vec4>), asCALL_GENERIC);
		engine->RegisterObjectMethod("vec4", "vec4 opAdd(float)", asFUNCTION(GLMHelper::opAdd<glm::vec4>), asCALL_GENERIC);
		engine->RegisterObjectMethod("vec4", "vec4 opSub(float)", asFUNCTION(GLMHelper::opSub<glm::vec4>), asCALL_GENERIC);
		engine->RegisterObjectMethod("vec4", "vec4 opMul(float)", asFUNCTION(GLMHelper::opMul<glm::vec4>), asCALL_GENERIC);
		engine->RegisterObjectMethod("vec4", "vec4 opDiv(float)", asFUNCTION(GLMHelper::opDiv<glm::vec4>), asCALL_GENERIC);

		engine->RegisterObjectMethod("vec4", "float opIndex(int)", asFUNCTION(GLMHelper::opIndex<glm::vec4>), asCALL_GENERIC);
	}

	void GLMHelper::RegisterMat2(asIScriptEngine *engine)
	{
		engine->RegisterObjectType("mat2", sizeof(glm::mat2), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS);
		engine->RegisterObjectMethod("mat2", "vec2& opIndex(int)", asFUNCTION(GLMHelper::opIndex<glm::mat2>), asCALL_GENERIC);

	}

	void GLMHelper::RegisterMat3(asIScriptEngine *engine)
	{
		engine->RegisterObjectType("mat3", sizeof(glm::mat2), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS);
		engine->RegisterObjectMethod("mat3", "vec3& opIndex(int)", asFUNCTION(GLMHelper::opIndex<glm::mat3>), asCALL_GENERIC);
	}

	void GLMHelper::RegisterMat4(asIScriptEngine *engine)
	{
		engine->RegisterObjectType("mat2", sizeof(glm::mat2), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS);
		engine->RegisterObjectMethod("mat3", "vec3& opIndex(int)", asFUNCTION(GLMHelper::opIndex<glm::mat4>), asCALL_GENERIC);
	}
}