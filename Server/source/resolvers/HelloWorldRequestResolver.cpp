#include "HelloWorldRequestResolver.hpp"

HelloWorldRequestResolver::HelloWorldRequestResolver(const std::string & type)
    : RequestResolverAbstract(type)
{

}

bool HelloWorldRequestResolver::resolve(tcp::socket & socket, const Request & request)
{
    if (request.getType() != m_type)
        return false;

    write(socket, "Hello world!");
    return true;
}