#include "Resolver.hpp"

Resolver::Resolver()
{
    m_chain.push_back(std::unique_ptr<HelloWorldRequestResolver>(new HelloWorldRequestResolver("hello world")));
}

bool Resolver::resolve(tcp::socket & socket, const Request & request)
{
    for (auto & i : m_chain)
        if (i->resolve(socket, request))
            return true;
    return false;
}