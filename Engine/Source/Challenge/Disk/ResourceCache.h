#pragma once

#include <Challenge/Challenge.h>

namespace challenge
{
	template <typename T>
	struct ResourceHandle
	{
		long key;
		std::shared_ptr<T> object;

		ResourceHandle(long _key, T &_object) :
			key(_key), object(std::make_shared<T>(_object))
		{
		}
	};

	static const int kDefaultResourceCacheSize = 50;

	template <typename T>
	class ResourceCache
	{
		typedef std::vector<ResourceHandle<T> > TResourceCache;

	public:
		ResourceCache(int maxSize = kDefaultResourceCacheSize);
		~ResourceCache();

		std::shared_ptr<T> AddResource(long key, T &resource);
		void RemoveResource(long key);
		void RemoveResource(T *resource);

		std::shared_ptr<T> RetrieveResource(long key);


	private:
		TResourceCache mResources;
	};
};

#include <Challenge/Disk/ResourceCache.inl>
