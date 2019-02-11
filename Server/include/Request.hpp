#pragma once

#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <boost/asio.hpp>

class Request
{
public:
    Request() = default;
    Request(const std::string & message);

    const std::string & getType() const;
    const std::string & getMessage() const;
    const std::string & getVar(const std::string & key) const;

private:
    void parseVars(const std::string & vars);
    std::vector<std::string> splitString(const std::string & str, const char delimiter) const;

    std::string m_type;
    std::string m_message;
    std::map<std::string, std::string> m_variables;
};

class RequestException : public std::exception
{
public:
    explicit RequestException(const std::string & message);
    virtual const char * what() const throw() {
        return m_message.c_str();
    }
private:
    std::string m_message;
};