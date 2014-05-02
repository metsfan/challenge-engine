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

	}

	void GLMHelper::RegisterVec4(asIScriptEngine *engine)
	{

	}
}