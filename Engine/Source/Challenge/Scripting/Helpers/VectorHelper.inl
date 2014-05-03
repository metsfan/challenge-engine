#include <Challenge/Scripting/Helpers/VectorHelper.h>
#include <Challenge/Scripting/Helpers/ScriptBasics.h>

namespace challenge
{
	template <typename T>
	class _VectorHelper
	{
	public:
		static void erase(std::vector<T> &vec, int index)
		{
			vec.erase(vec.begin() + index);
		}

		static T& front(std::vector<T> &vec)
		{
			return vec.front();
		}

		static T& back(std::vector<T> &vec)
		{
			return vec.back();
		}

		static std::vector<T>& assign(std::vector<T> &vec, std::vector<T> &other)
		{
			vec = other;
			return vec;
		}
	};

	template <typename T>
	void VectorHelper::Register(asIScriptEngine *engine, const std::string &typeName, std::string vectorName)
	{
		if (vectorName.length() == 0) {
			vectorName = "vector_" + typeName;
		}

		std::string fn;

		engine->RegisterObjectType(vectorName.c_str(), sizeof(std::vector<T>), asOBJ_VALUE | asOBJ_APP_CLASS);

		engine->RegisterObjectBehaviour(vectorName.c_str(), asBEHAVE_CONSTRUCT, "void f()",
			asFUNCTION(ScriptBasics::Construct<std::vector<T>>), asCALL_CDECL_OBJFIRST); 
		engine->RegisterObjectBehaviour(vectorName.c_str(), asBEHAVE_DESTRUCT, "void f()",
			asFUNCTION(ScriptBasics::Destruct<std::vector<T>>), asCALL_CDECL_OBJFIRST);

		fn = "void push_back(const " + typeName + " &in)";
		engine->RegisterObjectMethod(vectorName.c_str(), fn.c_str(), asMETHODPR(std::vector<T>, push_back, (const T &), void), asCALL_THISCALL);
		engine->RegisterObjectMethod(vectorName.c_str(), "int size()", asMETHOD(std::vector<T>, size), asCALL_THISCALL);
		engine->RegisterObjectMethod(vectorName.c_str(), "void erase(int)", asFUNCTION(_VectorHelper<T>::erase), asCALL_CDECL_OBJFIRST);
		fn = "const " + typeName + "& opIndex(int)";
		engine->RegisterObjectMethod(vectorName.c_str(), fn.c_str(), asMETHODPR(std::vector<T>, operator[], (size_t), T&), asCALL_THISCALL);
		fn = "const " + typeName + "& at(int)";
		engine->RegisterObjectMethod(vectorName.c_str(), fn.c_str(), asMETHODPR(std::vector<T>, operator[], (size_t) const, const T&), asCALL_THISCALL);
		engine->RegisterObjectMethod(vectorName.c_str(), "void clear()", asMETHOD(std::vector<T>, clear), asCALL_THISCALL);
		engine->RegisterObjectMethod(vectorName.c_str(), "void reserve(int)", asMETHODPR(std::vector<T>, reserve, (size_t), void), asCALL_THISCALL);
		engine->RegisterObjectMethod(vectorName.c_str(), "void resize(int)", asMETHODPR(std::vector<T>, resize, (size_t), void), asCALL_THISCALL);
		fn = "const " + typeName + "& front()";
		engine->RegisterObjectMethod(vectorName.c_str(), fn.c_str(), asFUNCTION(_VectorHelper<T>::front), asCALL_CDECL_OBJFIRST);
		fn = "const " + typeName + "& back()";
		engine->RegisterObjectMethod(vectorName.c_str(), fn.c_str(), asFUNCTION(_VectorHelper<T>::back), asCALL_CDECL_OBJFIRST);
		engine->RegisterObjectMethod(vectorName.c_str(), "bool empty()", asMETHOD(std::vector<T>, empty), asCALL_THISCALL);
		fn = "void opAssign(const " + vectorName + " &in)";
		engine->RegisterObjectMethod(vectorName.c_str(), fn.c_str(), asFUNCTION(_VectorHelper<T>::assign), asCALL_CDECL_OBJFIRST);
	}
}