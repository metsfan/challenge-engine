#pragma once

#include <Challenge/Challenge.h>

#include <angelscript/angelscript.h>

namespace challenge
{
	class ScriptRefCounter
	{
	public:
		ScriptRefCounter() :
			mRefCount(1)
		{
		}

		virtual ~ScriptRefCounter()
		{
		}

		void AddRef()
		{
			mRefCount++;
		}

		void Release()
		{
			mRefCount--;
		
			if (mRefCount == 0) {
				delete this;
			}
		}

	private:
		int mRefCount;
	};
};