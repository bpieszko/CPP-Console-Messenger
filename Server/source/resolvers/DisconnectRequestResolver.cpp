#include "DisconnectRequestResolver.hpp"

/*
 *  @Brief:
 *      Constuctor initializing type of resolver (should be unique).
 *  @Args:
 *      type - type of resolver
 */
DisconnectRequestResolver::DisconnectRequestResolver(const std::string & type)
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
bool DisconnectRequestResolver::resolve(tcp::socket & socket, const Request & request)
{
    if (request.getType() != m_type)
        return false;

    try
    {
        if (!isUserExists(request.getVar("login")))
        {
            write(socket, "warning message\nLogin are incorrect.");
            return true;
        }

        disconnectUser(request.getVar("login"));
        write(socket, "message\nCorrectly disconnected user.");
    }
    catch (DatabaseException & e)
    {
        write(socket, "warning message\nCannot connect to database.");
    }

    return true;
}

/*
 *  @Brief:
 *      Method to disconnect user by login.
 *  @Args:
 *      login - user's login to disconnect
 */
void DisconnectRequestResolver::disconnectUser(const std::string & login)
{
    SQLResult result = Database::doQuery("UPDATE users SET online = 0 WHERE login = \'" + login + "\'");
}

/*
 *  @Brief:
 *      Method to check if user exists in database.
 *  @Args:
 *      login - user's login to check
 *  @Return:
 *      True if it is exists in database, false otherwise.
 */
bool DisconnectRequestResolver::isUserExists(const std::string & login) const
{
    SQLResult result = Database::doQuery("SELECT 1 FROM users WHERE login = \'" + login + "\'");
    
    if (result.size() > 0)
        return true;

    return false;
}