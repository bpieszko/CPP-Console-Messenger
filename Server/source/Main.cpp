#include "Server.hpp"

int main ()
{
    Server server(9984, "Log.txt");
    server.startListening();
    return 0;
}