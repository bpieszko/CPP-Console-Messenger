#include "Server.hpp"

int main ()
{
    Server server(9984);
    server.startListening();
    return 0;
}