#include "Database.hpp"

SQLResult Database::doQuery(const std::string & query)
{
    SQLResult result;

    MYSQL mysql;
    mysql_init(&mysql);

    if (!mysql_real_connect(&mysql, DB_IP, DB_LOGIN, DB_PASS, DB_DB, 0, NULL, 0))
        throw DatabaseException("Cannot connect to database.");

    MYSQL_RES * queryId;
    MYSQL_ROW row;

    mysql_select_db(&mysql, query.c_str());
    queryId = mysql_store_result(&mysql);

    while ((row = mysql_fetch_row(queryId)) != NULL)
    {
        result.push_back(std::vector<std::string>());
        for (int i = 0; i < mysql_num_fields(queryId); ++i)
        {
            result.back().push_back(row[i]);
        }
    }

    mysql_close(&mysql);

    return result;
}