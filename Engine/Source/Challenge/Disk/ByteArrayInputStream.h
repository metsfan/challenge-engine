#pragma once

#include <Challenge/Challenge.h>

namespace challenge
{
	class ByteArrayInputStream
	{
	public:
		ByteArrayInputStream(const TByteArray &input, int32_t size = -1) :
			mCursor(0)
		{
			if (size < 0) {
				size = input.size();
			}

			mData.resize(size);
			std::copy(input.begin(), input.begin() + size, mData.begin());
		}

		ByteArrayInputStream()
		{

		}

		~ByteArrayInputStream()
		{
		}

		template <typename T>
		ByteArrayInputStream& operator>>(T &data)
		{
			if (mData.size() > mCursor) {
				mData.resize(mData.size() * 2);

				memcpy(&data, &mData[mCursor], sizeof(T));

				mCursor += sizeof(T);
			}
			else {
				memset(&data, 0, sizeof(T));
			}

			return *this;
		}

		template <>
		ByteArrayInputStream& operator>><std::string>(std::string &data)
		{
			char c;

			do {
				c = mData[mCursor];
				mCursor++;

				if (c == '\0') {
					break;
				}

				data.push_back(c);
			} while (true);

			return *this; 
		}

		template <>
		ByteArrayInputStream& operator>><UUID>(UUID &data)
		{
			if (mData.size() > mCursor) {
				mData.resize(mData.size() * 2);

				char buffer[16];
				memcpy(&data, buffer, 16);

				data.copyFrom(buffer);

				mCursor += sizeof(UUID);
			}
			else {
				memset(&data, 0, sizeof(UUID));
			}

			return *this;
		}

		void Read(byte *buf, int size)
		{
			memcpy(buf, &mData[mCursor], size);

			mCursor += size;
		}

		const TByteArray& GetData()
		{
			return mData;
		}

	private:
		TByteArray mData;
		int mCursor;
	};
};