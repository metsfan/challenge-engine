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

	class IResource
	{
		virtual const void * GetData() = 0;
		virtual const size_t GetDataSize() = 0;
		virtual void UpdateData(const void *newData, const size_t newSize) = 0;
	};

	class Resource
	{
	public:
		Resource(std::string filepath);
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