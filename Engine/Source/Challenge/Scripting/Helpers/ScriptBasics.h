#pragma once

#include <Challenge/Challenge.h>

#include <new>

namespace challenge
{
	class ScriptBasics
	{
	public:

		template <typename T>
		static T * Construct(void *memory)
		{
			return new (memory) T();
		}

		template <typename T, typename... Args>
		static T * ConstructEx(void *memory, Args... args)
		{
			return new (memory) T(args...);
		}

		template <typename T>
		static void Destruct(void *memory)
		{
			reinterpret_cast<T *>(memory)->~T();
		}

		template <typename T>
		static T * Factory()
		{
			return new T();
		}

		template <typename T>
		static T * TemplateFactory(asIObjectType *type)
		{
			return new T();
		}
	};
};