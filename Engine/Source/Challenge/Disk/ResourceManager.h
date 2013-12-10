#pragma once

#include <Challenge/Core/Globals.h>

namespace challenge
{
	template <typename T>
	class ResourceManager
	{
	public:
		ResourceManager();
		~ResourceManager();

		T * CreateFromFile(const std::string &key, std::string &filepath);
		T * CreateFromMemory(const std::string &key, void *data, const size_t size);

		T * Find(const std::string &key);


	private:
		std::map<std::string, T *> mResourceCache;
	};
};