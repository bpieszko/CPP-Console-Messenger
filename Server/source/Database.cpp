#include "Database.hpp"

/*
 *  @Brief:
 *      Performs query on database.
 *  @Args:
 *      query - query to perform on database
 *  @Return:
 *      Result from database in SQLResult format
 *      defined in Database.hpp.
 */
SQLResult Database::doQuery(const std::string & query)
{
    SQLResult result;

    MYSQL * mysql = mysql_init(NULL);

    if (!mysql_real_connect(mysql, DB_IP, DB_LOGIN, DB_PASS, DB_DB, 0, NULL, 0))
        throw DatabaseException("Cannot connect to database.");

    MYSQL_RES * queryId;
    MYSQL_ROW row;

    mysql_query(mysql, query.c_str());
    queryId = mysql_store_result(mysql);

    while (queryId && (row = mysql_fetch_row(queryId)) != NULL)
    {
        result.push_back(std::vector<std::string>());
        
        for (int i = 0; i < mysql_num_fields(queryId); ++i)
        {
            result.back().push_back(row[i]);
        }
    }

    mysql_close(mysql);

    return result;
}