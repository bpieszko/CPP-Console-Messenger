#include "RegisterRequestResolver.hpp"

RegisterRequestResolver::RegisterRequestResolver(const std::string & type)
    : RequestResolverAbstract(type)
{

}

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

bool RegisterRequestResolver::isUserExists(const std::string & login) const
{
    SQLResult result = Database::doQuery("SELECT 1 FROM users WHERE login = \'" + login + "\'");
    
    if (result.size() > 0)
        return true;

    return false;
}

void RegisterRequestResolver::registerUser(const std::string & login, const std::string & password) const
{
    SQLResult result = Database::doQuery("INSERT INTO users (login, password, online) VALUES (\'" + login + "\', \'" + password + "\', 0)");
}