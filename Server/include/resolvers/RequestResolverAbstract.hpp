#pragma once

#include <string>
#include <boost/asio.hpp>
#include "Request.hpp"

using namespace boost::asio;
using ip::tcp;

class RequestResolverAbstract
{
public:
    RequestResolverAbstract() = delete;
    RequestResolverAbstract(const std::string & type) : m_type(type) {}
    virtual bool resolve(tcp::socket & socket, const Request & request) = 0;

protected:
    const std::string m_type;
    
    const std::string read(tcp::socket & socket) const;
    void write(tcp::socket & socket, const std::string & message) const;
};