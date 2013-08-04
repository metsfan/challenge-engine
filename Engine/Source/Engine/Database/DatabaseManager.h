#pragma once

#include <Engine/Challenge.h>
#include <mysql_connection.h>
#include <mysql_driver.h>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#define DB_HOST "tcp://127.0.0.1:3306";

namespace challenge
{
	class DatabaseManager
	{
	public:
		DatabaseManager();
		bool Initialize();

		sql::ResultSet* ExecuteQuery(std::string query);
		void ExecuteUpdate(std::string query);

	private:
		sql::Connection *conn;
		sql::mysql::MySQL_Driver *driver;
	};
};