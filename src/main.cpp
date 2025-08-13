#include <stdio.h>
#include <spdlog/spdlog.h>
#include <server/Server.h>
#include <socket/SocketBase.h>

int main(int argc, char** argv)
{
    spdlog::info("Starting Main");

    webserver::Server server("10.0.0.128", 8080);

    server.Start();
    //webserver::SocketBase socket("10.0.0.49", 8000, AF_INET, SOCK_STREAM, 0);
    //socket.StartListening();
    return 0;
}