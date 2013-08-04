#pragma once

#include <Engine/Challenge.h>

namespace challenge
{
	template <typename T>
	struct Resource
	{
		long key;
		std::shared_ptr<T> object;

		Resource(long _key, T &_object) :
			key(_key), object(std::make_shared<T>(_object))
		{
		}
	};

	static const int kDefaultResourceCacheSize = 50;

	template <typename T>
	class ResourceCache
	{
		typedef std::vector<Resource<T> > TResourceCache;

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

#include <Engine/Resource/ResourceCache.inl>
