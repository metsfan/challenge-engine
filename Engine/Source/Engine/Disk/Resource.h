#pragma once

#include <Engine/Core/Globals.h>

namespace challenge
{
	enum ResourceType
	{
		ResourceTypeData,
		ResourceTypeImage,
		ResourceTypeModel
	};

	class Resource
	{
	public:
		Resource(const std::string &name);
		Resource(const void *data, const size_t size);
		virtual ~Resource();

		const void * GetData() { return mData; }
		const size_t GetDataSize() { return mDataSize; }

		void UpdateData(const void *newData, size_t newSize);

	private:
		void *mData;
		size_t mDataSize;
	};

};