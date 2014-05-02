#pragma once

#include <Challenge/Challenge.h>
#include <angelscript/angelscript.h>

#include <Challenge/Scripting/Helpers/ScriptRefCounter.h>

namespace challenge
{
	class ScriptVector : public ScriptRefCounter
	{
	public:
		ScriptVector();
		~ScriptVector();

		void push_back(void *object)
		{
			mVector.push_back(object);
		}

		size_t size() const
		{
			return mVector.size();
		}

		void erase(size_t index) 
		{
			mVector.erase(mVector.begin() + index);
		}

		const void * operator[](size_t pos) const
		{
			return mVector[pos];
		}

		void * operator[](size_t pos)
		{
			return mVector[pos];
		}

		void clear()
		{
			mVector.clear();
		}

		void reserve(size_t size)
		{
			mVector.reserve(size);
		}

		void resize(size_t size)
		{
			mVector.resize(size);
		}

		void * front() const
		{
			return mVector.front();
		}

		void * back() const
		{
			return mVector.back();
		}

		bool empty() const
		{
			return mVector.empty();
		}

		void operator=(ScriptVector &other)
		{
			mVector = other.mVector;
		}

		static void Register(asIScriptEngine *engine);

	private:
		int64_t padding;
		std::vector<void *> mVector;
	};
};