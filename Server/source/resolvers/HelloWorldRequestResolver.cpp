#include "HelloWorldRequestResolver.hpp"

/*
 *  @Brief:
 *      Constuctor initializing type of resolver (should be unique).
 *  @Args:
 *      type - type of resolver
 */
HelloWorldRequestResolver::HelloWorldRequestResolver(const std::string & type)
    : RequestResolverAbstract(type)
{

}

/*
 *  @Brief:
 *      Method to resolve request if it is
 *      possible by this class (chain of responsibility).
 *  @Args:
 *      socket
 *      request
 *  @Return:
 *      True if request was resolved by this class, false otherwise.
 */
bool HelloWorldRequestResolver::resolve(tcp::socket & socket, const Request & request)
{
    if (request.getType() != m_type)
        return false;

    write(socket, "Hello world!");
    return true;
}