#include "Server.hpp"

/*
 * @Brief:
 *      Constructor
 * @Args:
 *      port - number of port to listening
 */
Server::Server()
    : m_acceptor(m_io_service, tcp::endpoint(tcp::v4(), PORT)),
      m_resolver(new Resolver())
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
    Logger::write("Listening started.");

    while (true)
    {
        tcp::socket socket(m_io_service);

        m_acceptor.accept(socket);
        std::thread t(&Server::handleConnection, this, std::move(socket));
        t.detach();
    }
    
    Logger::write("Listening stopped.");
}

/*
 * @Brief:
 *      Method to resolving socket (thread method).
 * @Args:
 *      socket - moved object to this method
 */
void Server::handleConnection(tcp::socket socket)
{
    Logger::write("Opening connection to: " + socket.remote_endpoint().address().to_string() + ".");

    try
    {
        Request request(read(socket));
        
        Logger::write("Handling request '" + request.getType() + "' from " + socket.remote_endpoint().address().to_string());
        m_resolver->resolve(socket, request);
        Logger::write("Request '" + request.getType() + "' from " + socket.remote_endpoint().address().to_string() + " handled correctly.");
    }
    catch (std::exception & e)
    {
        Logger::write("Exception catched: " + std::string(e.what()));
    }

    Logger::write("Closing connection to: " + socket.remote_endpoint().address().to_string() + ".");
    
    socket.close();
}