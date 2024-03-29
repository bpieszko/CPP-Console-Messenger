#include "Resolver.hpp"

Resolver::Resolver()
{
    
}

bool Resolver::resolve(const Command & cmd)
{
    for (auto & i : m_chain)
        if (i->resolve(cmd))
            return true;

    return false;
}

const std::list<std::unique_ptr<CommandResolverAbstract>> & Resolver::getCommands() const
{
    return m_chain;
}