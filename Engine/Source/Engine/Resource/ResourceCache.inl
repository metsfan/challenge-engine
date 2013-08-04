namespace challenge
{
	template <typename T>
	ResourceCache<T>::ResourceCache(int maxSize = kDefaultResourceCacheSize)
	{
	}
	
	template <typename T>
	ResourceCache<T>::~ResourceCache()
	{
	}

	template <typename T>
	std::shared_ptr<T> ResourceCache<T>::AddResource(long key, T &resource)
	{
		std::shared_ptr<T> cachedResource = this->RetrieveResource(key);
		if(!cachedResource) {
			Resource<T> res(key, resource);
			mResources.push_back(res);

			return res.object;
		}

		return cachedResource;
	}

	template <typename T>
	void ResourceCache<T>::RemoveResource(long key)
	{
		auto it = mResources.begin();
		while(it != mResources.end()) {
			if((*it).key == key) {
				mResources.erase(it);
				return;
			}
		}
	}

	template <typename T>
	void ResourceCache<T>::RemoveResource(T *resource)
	{
		auto it = mResources.begin();
		while(it != mResources.end()) {
			if((*it).object == resource) {
				mResources.erase(it);
				return;
			}
		}
	}

	template <typename T>
	std::shared_ptr<T> ResourceCache<T>::RetrieveResource(long key)
	{
		for(Resource<T> &res : mResources) {
			if(res.key == key) {
				return res.object;
			}
		}

		return NULL;
	}
};
