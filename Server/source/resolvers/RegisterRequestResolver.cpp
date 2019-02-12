#include "RegisterRequestResolver.hpp"

/*
 *  @Brief:
 *      Constuctor initializing type of resolver (should be unique).
 *  @Args:
 *      type - type of resolver
 */
RegisterRequestResolver::RegisterRequestResolver(const std::string & type)
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
bool RegisterRequestResolver::resolve(tcp::socket & socket, const Request & request)
{
    if (request.getType() != m_type)
        return false;

    try
    {
        if (isUserExists(request.getVar("login")))
        {
            write(socket, "warning message\nLogin is already in use.");
            return true;
        }
        
        registerUser(request.getVar("login"), request.getVar("password"));
        write(socket, "message\nUser registered correctly.");
    }
    catch (DatabaseException & e)
    {
        write(socket, "warning message\nCannot connect to database.");
    }

    return true;
}

/*
 *  @Brief:
 *      Method to check if user exists in database.
 *  @Args:
 *      login - user's login to check
 *  @Return:
 *      True if it is exists in database, false otherwise.
 */
bool RegisterRequestResolver::isUserExists(const std::string & login) const
{
    SQLResult result = Database::doQuery("SELECT 1 FROM users WHERE login = \'" + login + "\'");
    
    if (result.size() > 0)
        return true;

    return false;
}

/*
 *  @Brief:
 *      Method to perform sign up operation in database.
 *  @Args:
 *      login - user's login to sign up
 *      password - user's password to sign up
 */
void RegisterRequestResolver::registerUser(const std::string & login, const std::string & password) const
{
    SQLResult result = Database::doQuery("INSERT INTO users (login, password, online) VALUES (\'" + login + "\', \'" + password + "\', 0)");
}