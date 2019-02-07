#include "Client.hpp"

Client::Client(const std::string & login, const std::string & password, const bool connected)
    : m_login(login), m_password(password), m_connected(connected)
{

}

const std::string & Client::getLogin() const
{
    return m_login;
}

const std::string & Client::getPassword() const
{
    return m_password;
}

const bool Client::isOnline() const
{
    return m_connected;
}

void Client::disconnect()
{
    m_connected = false;
}

void Client::connect()
{
    m_connected = false;
}