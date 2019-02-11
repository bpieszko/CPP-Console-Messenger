#include "HelloWorldRequestResolver.hpp"

HelloWorldRequestResolver::HelloWorldRequestResolver(const std::string & type)
    : RequestResolverAbstract(type)
{

}

bool HelloWorldRequestResolver::resolve(tcp::socket & socket, const Request & request)
{
    write(socket, "Hello world!");
}