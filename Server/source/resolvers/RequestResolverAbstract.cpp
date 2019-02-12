#include "RequestResolverAbstract.hpp"

/*
 * @Brief:
 *      Method to write data to socket.
 * @Args:
 *      socket - reference to socket
 *      message - message to send
 */
void RequestResolverAbstract::write(tcp::socket & socket, const std::string & message) const
{
    boost::asio::write(socket, boost::asio::buffer(message + "\n"));
}

/*
 * @Brief:
 *      Method to read data from socket.
 * @Args:
 *      socket - reference to socket
 * @Return:
 *      Message from socket in std::string.
 */
const std::string RequestResolverAbstract::read(tcp::socket & socket) const
{
    boost::asio::streambuf buf;
    boost::asio::read_until(socket, buf, '\n');
    std::string data = boost::asio::buffer_cast<const char *>(buf.data());
    return data;
}