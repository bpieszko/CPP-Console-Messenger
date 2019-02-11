#pragma once

#include <list>
#include <memory>
#include <boost/asio.hpp>
#include "RequestResolverAbstract.hpp"
#include "Request.hpp"

#include "HelloWorldRequestResolver.hpp"

using namespace boost::asio;
using ip::tcp;

class Resolver
{
public:
    Resolver();

    bool resolve(tcp::socket & socket, const Request & request);

private:
    std::list<std::unique_ptr<RequestResolverAbstract>> m_chain;
};