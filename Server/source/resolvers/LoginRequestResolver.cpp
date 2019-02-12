#include "LoginRequestResolver.hpp"

LoginRequestResolver::LoginRequestResolver(const std::string & type)
    : RequestResolverAbstract(type)
{

}

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

bool LoginRequestResolver::isUserExists(const std::string & login) const
{
    SQLResult result = Database::doQuery("SELECT 1 FROM users WHERE login = \'" + login + "\'");
    
    if (result.size() > 0)
        return true;

    return false;
}

bool LoginRequestResolver::isPasswordMatch(const std::string & login, const std::string & password) const
{
    SQLResult result = Database::doQuery("SELECT 1 FROM users WHERE login = \'" + login + "\' AND password = \'"+ password + "\'");

    if (result.size() > 0)
        return true;

    return false;
}

void LoginRequestResolver::loginUser(const std::string & login, const std::string & password) const
{
    SQLResult result = Database::doQuery("UPDATE users set online = 1 where login = \'" + login + "\' and password = \'" + password + "\'");
}