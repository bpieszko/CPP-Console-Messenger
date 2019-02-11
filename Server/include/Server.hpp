#pragma once

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <mutex>
#include "Request.hpp"
#include "Resolver.hpp"
#include "Logger.hpp"

using namespace boost::asio;
using ip::tcp;

class Server
{
public:
    Server() = delete;
    Server(const size_t port, const std::string & log_file);
    void startListening();

private:
    std::string read(tcp::socket & socket);
    void write(tcp::socket & socket, const std::string & message);

    void handleConnection(tcp::socket socket);

    boost::asio::io_service m_io_service;
    tcp::acceptor m_acceptor;
    std::unique_ptr<Resolver> m_resolver;
    std::unique_ptr<Logger> m_logger;
};