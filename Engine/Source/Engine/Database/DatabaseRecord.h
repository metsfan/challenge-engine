#pragma once

#include <Engine/Challenge.h>
#include <Engine/Database/DatabaseManager.h>

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

