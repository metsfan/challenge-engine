#pragma once

#include <Challenge/Challenge.h>

namespace challenge
{
	class ByteArrayOutputStream
	{
	public:
		ByteArrayOutputStream(int startSize = 128) :
			mSize(0)
		{
			mData.resize(startSize);
		}

		~ByteArrayOutputStream()
		{
		}

		template <typename T>
		ByteArrayOutputStream& operator<<(const T &data)
		{
			int cursor = mSize;

			this->AccomdateIncrease(sizeof(T));

			memcpy(&mData[cursor], &data, sizeof(T));

			return *this;
		}

		template <>
		ByteArrayOutputStream& operator<<<std::string>(const std::string &data)
		{
			int cursor = mSize;

			this->AccomdateIncrease(data.length() + 1);

			memcpy(&mData[cursor], &data[0], data.length());
			mData.push_back('\0');

			return *this;
		}

		template <>
		ByteArrayOutputStream& operator<<<TByteArray>(const TByteArray &data)
		{
			int cursor = mSize;

			this->AccomdateIncrease(data.size() + 1);

			memcpy(&mData[cursor], &data[0], data.size());

			return *this;
		}

		TByteArray GetData()
		{
			TByteArray output;
			output.resize(mSize);
			std::copy(mData.begin(), mData.begin() + mSize, output.begin());

			return output;
		}

	private:
		TByteArray mData;
		int mSize;

		void AccomdateIncrease(int size)
		{
			mSize += size;

			if (mData.size() < mSize) {
				mData.resize(mData.size() * 2);
			}
		}
	};
};