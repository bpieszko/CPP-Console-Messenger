#include "Server.hpp"

/*
 * @Brief:
 *      Constructor
 * @Args:
 *      port - number of port to listening
 */
Server::Server(const size_t port, const std::string & log_file)
    : m_acceptor(m_io_service, tcp::endpoint(tcp::v4(), port)),
      m_resolver(new Resolver()),
      m_logger(new Logger(log_file))
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
    m_logger->write("Listening started.");

    while (true)
    {
        tcp::socket socket(m_io_service);

        m_acceptor.accept(socket);
        std::thread t(&Server::handleConnection, this, std::move(socket));
        t.detach();
    }
    
    m_logger->write("Listening stopped.");
}

/*
 * @Brief:
 *      Method to resolving socket (thread method).
 * @Args:
 *      socket - moved object to this method
 */
void Server::handleConnection(tcp::socket socket)
{
    m_logger->write("Opening connection to: " + socket.remote_endpoint().address().to_string() + ".");

    try
    {
        Request request(read(socket));
        
        m_logger->write("Handling request '" + request.getType() + "' from " + socket.remote_endpoint().address().to_string());
        m_resolver->resolve(socket, request);
        m_logger->write("Request '" + request.getType() + "' from " + socket.remote_endpoint().address().to_string() + " handled correctly.");
    }
    catch (std::exception & e)
    {
        m_logger->write("Exception catched: " + std::string(e.what()));
    }

    m_logger->write("Closing connection to: " + socket.remote_endpoint().address().to_string() + ".");
    
    socket.close();
}