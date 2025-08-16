#include <stdio.h>
#include <spdlog/spdlog.h>
#include <server/Server.h>

int main(int argc, char** argv)
{
    spdlog::info("Starting Main");

    webserver::Server server("0.0.0.0", 8080);

    server.Start();

    return 0;
}