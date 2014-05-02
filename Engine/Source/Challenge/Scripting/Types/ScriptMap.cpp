#include <Challenge/Challenge.h>
#include <Challenge/Scripting/Types/ScriptMap.h>
#include <Challenge/Scripting/Helpers/ScriptBasics.h>
#include <Challenge/Scripting/Helpers/ScriptUtil.h>

#include <Challenge/Scripting/Types/ScriptVector.h>

namespace challenge
{
	void ScriptMap::insert(const void * key, const void * value)
	{
		int64_t keyValue = this->GetValue(key, mKeyIsPrimitive, mKeyIsLong);
		int64_t valueValue = this->GetValue(value, mValueIsPrimitive, mValueIsLong);

		mMap.insert(std::pair<int64_t, int64_t>(keyValue, valueValue));
	}

	void * ScriptMap::operator[](const void *key)
	{
		int64_t keyValue = this->GetValue(key, mKeyIsPrimitive, mKeyIsLong);

		auto it = mMap.find(keyValue);
		if (it != mMap.end()) {
			void *valueValue = (void *) it->second;
			if (mValueIsPrimitive) {
				valueValue = (void *) &it->second;
			}
			return valueValue;
		}

		return NULL;
	}

	void ScriptMap::erase(const void *key)
	{
		int64_t keyValue = this->GetValue(key, mKeyIsPrimitive, mKeyIsLong);

		mMap.erase(keyValue);
	}

	void * ScriptMap::next()
	{
		void *returnPtr = (void *)mIterCursor->first;

		if (mKeyIsPrimitive) {
			returnPtr = (void *) &mIterCursor->first;
		}
		
		mIterCursor++;
	
		return returnPtr;
	}

	void ScriptMap::operator=(ScriptMap &other)
	{
		mMap = other.mMap;
		mKeyIsPrimitive = other.mKeyIsPrimitive;
		mValueIsPrimitive = other.mValueIsPrimitive;
		mKeyIsLong = other.mKeyIsLong;
		mValueIsLong = other.mValueIsLong;
	}

	int64_t ScriptMap::GetValue(const void *ptr, bool isPrimitive, bool isLong)
	{
		int64_t value;

		if (isPrimitive) {
			if (isLong) {
				value =  *(int64_t *) ptr;
			} else {
				value = (int64_t) *(int *) ptr;
			}
		}
		else {
			value = (int64_t) ptr;
		}
		 
		return value;
	}

	void ScriptMap::Register(asIScriptEngine *engine)
	{
		engine->RegisterObjectType("map<class K, class V>", 0, asOBJ_REF | asOBJ_TEMPLATE);

		engine->RegisterObjectBehaviour("map<K,V>", asBEHAVE_ADDREF, "void f()", asMETHOD(ScriptMap, AddRef), asCALL_THISCALL);
		engine->RegisterObjectBehaviour("map<K,V>", asBEHAVE_RELEASE, "void f()", asMETHOD(ScriptMap, Release), asCALL_THISCALL);
		engine->RegisterObjectBehaviour("map<K,V>", asBEHAVE_FACTORY, "map<K,V>@ f(int &in)",
			asFUNCTION(ScriptMap::TemplateFactory), asCALL_CDECL);

		engine->RegisterObjectMethod("map<K,V>", "void insert(const K &in, const V &in)", asMETHOD(ScriptMap, insert), asCALL_THISCALL);
		engine->RegisterObjectMethod("map<K,V>", "V& opIndex(const K &in)", asMETHOD(ScriptMap, operator[]), asCALL_THISCALL);
		engine->RegisterObjectMethod("map<K,V>", "void erase(const K &in)", asMETHOD(ScriptMap, erase), asCALL_THISCALL);
		engine->RegisterObjectMethod("map<K,V>", "void begin()", asMETHOD(ScriptMap, begin), asCALL_THISCALL);
		engine->RegisterObjectMethod("map<K,V>", "K& next()", asMETHOD(ScriptMap, next), asCALL_THISCALL);
		engine->RegisterObjectMethod("map<K,V>", "bool hasNext()", asMETHOD(ScriptMap, hasNext), asCALL_THISCALL);
		engine->RegisterObjectMethod("map<K,V>", "void opAssign(const map<K,V> &in)", asMETHOD(ScriptMap, operator=), asCALL_THISCALL);
		engine->RegisterObjectMethod("map<K,V>", "int size()", asMETHOD(ScriptMap, size), asCALL_THISCALL);
		engine->RegisterObjectMethod("map<K,V>", "void clear()", asMETHOD(ScriptMap, clear), asCALL_THISCALL);
	}

	ScriptMap * ScriptMap::TemplateFactory(asIObjectType *type)
	{
		ScriptMap *object = ScriptBasics::TemplateFactory<ScriptMap>(type);

		int typeIdKey = type->GetSubTypeId(0);
		if (ScriptUtil::IsPrimitiveType(typeIdKey)) {
			object->mKeyIsPrimitive = true;
			if (typeIdKey == asTYPEID_INT64 ||
				typeIdKey == asTYPEID_UINT64 ||
				typeIdKey == asTYPEID_DOUBLE) {
				object->mKeyIsLong = true;
			}
		}

		
		int typeIdValue = type->GetSubTypeId(1);
		if (ScriptUtil::IsPrimitiveType(typeIdValue)) {
			object->mValueIsPrimitive = true;
			if (typeIdValue == asTYPEID_INT64 ||
				typeIdValue == asTYPEID_UINT64 ||
				typeIdValue == asTYPEID_DOUBLE) {
				object->mValueIsLong = true;
			}
		}

		return object;
	}
}