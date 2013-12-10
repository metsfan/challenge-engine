#include <Challenge/Challenge.h>
#include "DatabaseManager.h"
using namespace challenge;

DatabaseManager::DatabaseManager()
{
	conn = NULL;
	driver = sql::mysql::get_mysql_driver_instance();
}

bool DatabaseManager::Initialize()
{
	sql::SQLString hostName = (sql::SQLString)DB_HOST;

	try {
		conn = driver->connect(hostName+"/dungeon_raider", "root", "");
	} catch(sql::SQLException &e) {
		return false;
	}
	return true;
}

sql::ResultSet* DatabaseManager::ExecuteQuery(std::string query)
{
	try {
		sql::Statement *stmt = conn->createStatement();
	
		sql::ResultSet *resultSet = stmt->executeQuery(query);

		delete stmt;

		return resultSet;
	} catch(sql::SQLException &e) {
		printf("stop");
	}
	return NULL;
}

void DatabaseManager::ExecuteUpdate(std::string query)
{
	sql::Statement *stmt = conn->createStatement();
	
	stmt->executeUpdate(query);

	delete stmt;
}