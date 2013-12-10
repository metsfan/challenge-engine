#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Database/DatabaseManager.h>

namespace challenge
{
	class DatabaseRecord
	{
	public:
		DatabaseRecord();
		~DatabaseRecord();

	protected:
		DatabaseManager *mManager;
	};
};

