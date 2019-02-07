#pragma once

#include <string>

class Client
{
public:
    Client() = delete;
    Client(const std::string & login, const std::string & password, const bool connected);

    const std::string & getLogin() const;
    const std::string & getPassword() const;
    const bool isOnline() const;
    
    void disconnect();
    void connect();

private:
    std::string m_login;
    std::string m_password;
    bool m_connected;
};