#include "Resolver.hpp"

/*
 *  @Brief:
 *      Constructor.
 *      m_chain has resolver objects. 
 */
Resolver::Resolver()
{
    m_chain.push_back(std::unique_ptr<HelloWorldRequestResolver>(new HelloWorldRequestResolver("hello world")));
    m_chain.push_back(std::unique_ptr<RegisterRequestResolver>(new RegisterRequestResolver("register")));
    m_chain.push_back(std::unique_ptr<LoginRequestResolver>(new LoginRequestResolver("login")));
    m_chain.push_back(std::unique_ptr<DisconnectRequestResolver>(new DisconnectRequestResolver("disconnect")));
}

/*
 *  @Brief:
 *      Resolve method in chain of responsibility.
 *  @Args:
 *      socket - reference to socket
 *      request - request message to resolve
 *  @Return:
 *      Returns true if request has been resolved.
 *      Returns false othrewise.
 */
bool Resolver::resolve(tcp::socket & socket, const Request & request)
{
    for (auto & i : m_chain)
        if (i->resolve(socket, request))
            return true;
    return false;
}