#include <Engine/Challenge.h>
#include <Engine/GameApplication.h>
#include "DatabaseRecord.h"
using namespace challenge;

DatabaseRecord::DatabaseRecord(void)
{
	mManager = GameApplication::GetInstance()->GetDatabaseManager();
}


DatabaseRecord::~DatabaseRecord(void)
{
}
