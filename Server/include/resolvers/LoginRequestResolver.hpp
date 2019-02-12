#pragma once

#include "RequestResolverAbstract.hpp"
#include "Database.hpp"
#include "Request.hpp"
#include "Logger.hpp"

class LoginRequestResolver : public RequestResolverAbstract
{
public:
    LoginRequestResolver() = delete;
    LoginRequestResolver(const std::string & type);
    virtual bool resolve(tcp::socket & socket, const Request & request);
private:
    void loginUser(const std::string & login, const std::string & password) const;
    bool isUserExists(const std::string & login) const;
    bool isPasswordMatch(const std::string & login, const std::string & password) const;
};