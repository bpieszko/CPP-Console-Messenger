#pragma once

#include <vector>
#include <string>
#include <mysql/mysql.h>
#include "Config.hpp"

using SQLResult = std::vector<std::vector<std::string>>;

class Database
{
public:
    Database() = delete;
    
    static SQLResult doQuery(const std::string & query);

private:
    
};

class DatabaseException : public std::exception
{
public:
    explicit DatabaseException(const std::string & message)
        : m_message(message) { };
    virtual const char * what() const throw() {
        return m_message.c_str();
    }
private:
    std::string m_message;
};