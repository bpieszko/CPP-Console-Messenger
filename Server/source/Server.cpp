#include "Server.hpp"

/*
 * @Brief:
 *      Constructor
 * @Args:
 *      port - number of port to listening
 */
Server::Server(const size_t port)
    : m_acceptor(m_io_service, tcp::endpoint(tcp::v4(), port))
{
    
}

/*
 * @Brief:
 *      Method to read data from socket.
 * @Args:
 *      socket - reference to socket
 * @Return:
 *      Message from socket in std::string.
 */
std::string Server::read(tcp::socket & socket)
{
    boost::asio::streambuf buf;
    boost::asio::read_until(socket, buf, '\n');
    std::string data = boost::asio::buffer_cast<const char *>(buf.data());
    return data;
}

/*
 * @Brief:
 *      Method to write data to socket.
 * @Args:
 *      socket - reference to socket
 *      message - message to send
 */
void Server::write(tcp::socket & socket, const std::string & message)
{
    boost::asio::write(socket, boost::asio::buffer(message + "\n"));
}

/*
 * @Brief:
 *      Main loop of server handling requests.
 */
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

/*
 * @Brief:
 *      Method to resolving socket (thread method).
 * @Args:
 *      socket - moved object to this method
 */
void Server::handleConnection(tcp::socket socket)
{
    

    socket.close();
}