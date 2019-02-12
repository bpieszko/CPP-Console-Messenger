#include "LoginRequestResolver.hpp"

/*
 *  @Brief:
 *      Constuctor initializing type of resolver (should be unique).
 *  @Args:
 *      type - type of resolver
 */
LoginRequestResolver::LoginRequestResolver(const std::string & type)
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
bool LoginRequestResolver::resolve(tcp::socket & socket, const Request & request)
{
    if (request.getType() != m_type)
        return false;
    
    try
    {
        if (!isUserExists(request.getVar("login")))
        {
            write(socket, "warning message\nLogin or password are incorrect.");
            return true;
        }

        if (!isPasswordMatch(request.getVar("login"), request.getVar("password")))
        {
            write(socket, "warning message\nLogin or password are incorrect.");
            return true;
        }

        loginUser(request.getVar("login"), request.getVar("password"));
        write(socket, "message\nUser logged in correctly.");
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
bool LoginRequestResolver::isUserExists(const std::string & login) const
{
    SQLResult result = Database::doQuery("SELECT 1 FROM users WHERE login = \'" + login + "\'");
    
    if (result.size() > 0)
        return true;

    return false;
}

/*
 *  @Brief:
 *      Method to check if password match with this in database.
 *  @Args:
 *      login - user's login to check
 *      password - user's password to check
 *  @Return:
 *      True if password is correct, false otherwise.
 */
bool LoginRequestResolver::isPasswordMatch(const std::string & login, const std::string & password) const
{
    SQLResult result = Database::doQuery("SELECT 1 FROM users WHERE login = \'" + login + "\' AND password = \'"+ password + "\'");

    if (result.size() > 0)
        return true;

    return false;
}

/*
 *  @Brief:
 *      Method to perform sign in operation in database.
 *  @Args:
 *      login - user's login to sign in
 *      password - user's password to sign in
 */
void LoginRequestResolver::loginUser(const std::string & login, const std::string & password) const
{
    SQLResult result = Database::doQuery("UPDATE users set online = 1 where login = \'" + login + "\' and password = \'" + password + "\'");
}