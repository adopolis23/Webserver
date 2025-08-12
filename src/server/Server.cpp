#include "Server.h"

webserver::Server::Server(const char* ip, unsigned int port)
{
	spdlog::info("Initiallizing Server: Creating Socket...");

	m_socket = new SocketBase(ip, port, AF_INET, SOCK_STREAM, 0);
	m_socket->StartListening();
}

webserver::Server::~Server()
{
}
