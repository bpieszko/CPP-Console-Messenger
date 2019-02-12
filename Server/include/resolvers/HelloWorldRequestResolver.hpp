#pragma once

#include <string>
#include <iostream>
#include <boost/asio.hpp>
#include "Request.hpp"
#include "RequestResolverAbstract.hpp"

using namespace boost::asio;
using ip::tcp;

class HelloWorldRequestResolver : public RequestResolverAbstract
{
public:
    HelloWorldRequestResolver() = delete;
    HelloWorldRequestResolver(const std::string & type);
    virtual bool resolve(tcp::socket & socket, const Request & request);
};