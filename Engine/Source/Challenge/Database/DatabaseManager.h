#pragma once

#include <Challenge/Challenge.h>
#include <mysql/mysql_connection.h>
#include <mysql/mysql_driver.h>

#include <mysql/cppconn/driver.h>
#include <mysql/cppconn/exception.h>
#include <mysql/cppconn/resultset.h>
#include <mysql/cppconn/statement.h>
#include <mysql/cppconn/prepared_statement.h>

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