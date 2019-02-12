#pragma once

#include "RequestResolverAbstract.hpp"
#include "Database.hpp"
#include "Request.hpp"
#include "Logger.hpp"


class DisconnectRequestResolver : public RequestResolverAbstract
{
public:
    DisconnectRequestResolver() = delete;
    DisconnectRequestResolver(const std::string & type);

    virtual bool resolve(tcp::socket & socket, const Request & request);

private:
    void disconnectUser(const std::string & login);
    bool isUserExists(const std::string & login) const;
};