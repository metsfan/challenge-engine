#include <Challenge/Challenge.h>
#include <Challenge/Scripting/Types/ScriptVector.h>
#include <Challenge/Scripting/Helpers/ScriptBasics.h>

namespace challenge
{
	ScriptVector::ScriptVector()
	{
	}

	ScriptVector::~ScriptVector()
	{
	}

	void ScriptVector::Register(asIScriptEngine *engine)
	{
		engine->RegisterObjectType("vector<class T>", 0, asOBJ_REF | asOBJ_TEMPLATE);

		engine->RegisterObjectBehaviour("vector<T>", asBEHAVE_ADDREF, "void f()", asMETHOD(ScriptVector, AddRef), asCALL_THISCALL);
		engine->RegisterObjectBehaviour("vector<T>", asBEHAVE_RELEASE, "void f()", asMETHOD(ScriptVector, Release), asCALL_THISCALL);
		engine->RegisterObjectBehaviour("vector<T>", asBEHAVE_FACTORY, "vector<T>@ f(int &in)",
			asFUNCTION(ScriptBasics::TemplateFactory<ScriptVector>), asCALL_CDECL);

		engine->RegisterObjectMethod("vector<T>", "void push_back(const T &in)", asMETHOD(ScriptVector, push_back), asCALL_THISCALL);
		engine->RegisterObjectMethod("vector<T>", "int size()", asMETHOD(ScriptVector, size), asCALL_THISCALL);
		engine->RegisterObjectMethod("vector<T>", "void erase(int)", asMETHOD(ScriptVector, erase), asCALL_THISCALL);
		engine->RegisterObjectMethod("vector<T>", "const T& at(int)", asMETHODPR(ScriptVector, operator[], (size_t) const, const void *), asCALL_THISCALL);
		engine->RegisterObjectMethod("vector<T>", "T& opIndex(int)", asMETHODPR(ScriptVector, operator[], (size_t), void *), asCALL_THISCALL);
		engine->RegisterObjectMethod("vector<T>", "void clear()", asMETHOD(ScriptVector, clear), asCALL_THISCALL);
		engine->RegisterObjectMethod("vector<T>", "void reserve(int)", asMETHOD(ScriptVector, reserve), asCALL_THISCALL);
		engine->RegisterObjectMethod("vector<T>", "void resize(int)", asMETHOD(ScriptVector, resize), asCALL_THISCALL);
		engine->RegisterObjectMethod("vector<T>", "const T& front()", asMETHOD(ScriptVector, front), asCALL_THISCALL);
		engine->RegisterObjectMethod("vector<T>", "const T& back()", asMETHOD(ScriptVector, back), asCALL_THISCALL);
		engine->RegisterObjectMethod("vector<T>", "bool empty()", asMETHOD(ScriptVector, empty), asCALL_THISCALL);
		engine->RegisterObjectMethod("vector<T>", "void opAssign(const vector<T> &in)", asMETHOD(ScriptVector, operator=), asCALL_THISCALL);
	}
};