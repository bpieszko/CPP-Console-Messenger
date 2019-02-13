#pragma once

#include <boost/asio.hpp>
#include <string>
#include <iostream>
#include "Resolver.hpp"
#include "Command.hpp"

using namespace boost::asio;
using ip::tcp;

enum MSG_TYPE
{
    NORMAL,
    WARNING,
    ERROR
};

class Client
{
public:
    Client();

    void start();

private:
    void showMenu() const;
    const Command getCommand(const std::string & pre_msg) const;
    void handleCommand(const Command & cmd);
    void showMessage(MSG_TYPE type, const std::string & msg) const;

    io_service m_io_service;
    std::unique_ptr<Resolver> m_resolver;
};