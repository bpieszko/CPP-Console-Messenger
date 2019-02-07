#include "Server.hpp"

Server::Server(const size_t port)
    : m_acceptor(m_io_service, tcp::endpoint(tcp::v4(), port))
{
    
}

void Server::startListening()
{
    while (true)
    {
        tcp::socket socket(m_io_service);

        m_acceptor.accept(socket);
        std::thread t(&Server::handleConnection, this, std::move(socket));
        t.detach();
    }
}

std::string Server::read(tcp::socket & socket)
{
    boost::asio::streambuf buf;
    boost::asio::read_until(socket, buf, '\n');
    std::string data = boost::asio::buffer_cast<const char *>(buf.data());
    return data;
}

void Server::write(tcp::socket & socket, const std::string & message)
{
    boost::asio::write(socket, boost::asio::buffer(message + "\n"));
}

void Server::handleConnection(tcp::socket socket)
{
    try
    {
        Message message(read(socket));
        if (message.getType() == "join")
        {
            joinClient(socket, message);
        }
        else if (message.getType() == "login")
        {
            loginClient(socket, message);
        }
        else if (message.getType() == "register")
        {
            registerClient(socket, message);
        }
        else
        {
            throw "Cannot handle Client's request.";
        }    
    }
    catch(const char * e)
    {
        std::cout << e << std::endl;
    }
    socket.close();
}

void Server::joinClient(tcp::socket & socket, const Message & message)
{
    if (m_clients.find(message.getVar("nickname")) != m_clients.end())
    {
        write(socket, "login");
    }
    else
    {
        write(socket, "nickname_not_recognized");
    }
}

void Server::loginClient(tcp::socket & socket, const Message & message)
{
    std::lock_guard<std::mutex> lock(m_clients_mutex);
    
    if (m_clients.at(message.getVar("login")).getPassword() == message.getVar("password"))
    {
        m_clients.at(message.getVar("login")).connect();
        write(socket, "connected");
    }
    else
    {
        write(socket, "wrong_password");
    }
}

void Server::registerClient(tcp::socket & socket, const Message & message)
{
    std::lock_guard<std::mutex> lock(m_clients_mutex);
    
    Client client(message.getVar("login"), message.getVar("password"), 0);
    m_clients.insert({message.getVar("login"), client});

    write(socket, "registered");
}

