#include "RequestResolverAbstract.hpp"

void RequestResolverAbstract::write(tcp::socket & socket, const std::string & message) const
{
    boost::asio::write(socket, boost::asio::buffer(message + "\n"));
}

const std::string RequestResolverAbstract::read(tcp::socket & socket) const
{
    boost::asio::streambuf buf;
    boost::asio::read_until(socket, buf, '\n');
    std::string data = boost::asio::buffer_cast<const char *>(buf.data());
    return data;
}