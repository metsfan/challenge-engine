#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Scripting/Helpers/ScriptRefCounter.h>

namespace challenge
{
	class ScriptMap : public ScriptRefCounter
	{
	public:
		ScriptMap() :
			mKeyIsPrimitive(false),
			mValueIsPrimitive(false),
			mKeyIsLong(false),
			mValueIsLong(false)
		{
		}

		~ScriptMap()
		{
		}

		void insert(const void * key, const void * value);
		void * operator[](const void *key);
		void erase(const void *key);

		int size()
		{
			return mMap.size();
		}

		void clear()
		{
			mMap.clear();
		}

		void begin()
		{
			mIterCursor = mMap.begin();
		}

		void * next();

		bool hasNext()
		{
			return mIterCursor != mMap.end();
		}

		void operator=(ScriptMap &other);

		static void Register(asIScriptEngine *engine);

	private:
		std::map<int64_t, int64_t> mMap;
		std::map<int64_t, int64_t>::iterator mIterCursor;

		bool mKeyIsPrimitive;
		bool mKeyIsLong;
		bool mValueIsPrimitive;
		bool mValueIsLong;

		static ScriptMap * TemplateFactory(asIObjectType *type);

		int64_t GetValue(const void *ptr, bool isPrimitive, bool isLong);
	};
};