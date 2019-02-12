#pragma once

#include "RequestResolverAbstract.hpp"
#include "Request.hpp"
#include "Database.hpp"
#include "Logger.hpp"

using SQLResult = std::vector<std::vector<std::string>>;

class RegisterRequestResolver : public RequestResolverAbstract
{
public:
    RegisterRequestResolver() = delete;
    RegisterRequestResolver(const std::string & type);
    virtual bool resolve(tcp::socket & socket, const Request & request);

private:
    bool isUserExists(const std::string & login) const;
    void registerUser(const std::string & login, const std::string & password) const;
};

class RegisterRequestResolverException : public std::exception
{
public:
    explicit RegisterRequestResolverException(const std::string & message)
        : m_message(message) { };
    virtual const char * what() const throw() {
        return m_message.c_str();
    }
private:
    std::string m_message;
};