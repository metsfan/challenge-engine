#include <Challenge/Challenge.h>
#include "File.h"

#include <sys/types.h>
#include <sys/stat.h>

namespace challenge
{
	bool File::ReadData()
	{
		std::ifstream filestream;

		filestream.open(mFilepath.c_str(), std::ios::in | std::ios::binary);

		if (!filestream.is_open())
		{
			return false;
		}
		struct _stat fileStat;
		off_t size;
        
		int err = _wstat(mFilepath.c_str(), &fileStat );
		if (0 == err)
		{
			size = fileStat.st_size;
		}
		else
		{
			filestream.seekg(0, std::ios_base::end);
			size = filestream.tellg();
		}
        
		mData.resize(size);
		filestream.read((char*)&mData[0], size);
		filestream.close();

		return true;
	}
};