#pragma once

#include <string>
#include <boost/asio.hpp>
#include "Command.hpp"

using namespace boost::asio;
using ip::tcp;

class CommandResolverAbstract
{
public:
    CommandResolverAbstract() = delete;
    CommandResolverAbstract(const std::string & type)
        : m_type(type) {}
    virtual bool resolve(const Command & command) = 0;

protected:
    const std::string m_type;
};