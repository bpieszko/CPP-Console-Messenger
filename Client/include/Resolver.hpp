#pragma once

#include <list>
#include <memory>
#include <boost/asio.hpp>

#include "Command.hpp"
#include "CommandResolverAbstract.hpp"

using namespace boost::asio;
using ip::tcp;

class Resolver
{
public:
    Resolver();

    bool resolve(const Command & cmd);
    const std::list<std::unique_ptr<CommandResolverAbstract>> & getCommands() const;

private:
    std::list<std::unique_ptr<CommandResolverAbstract>> m_chain;
};