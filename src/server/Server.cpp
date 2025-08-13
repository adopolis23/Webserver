#include "Server.h"

webserver::Server::Server(const char* ip, unsigned int port)
: m_Running(false)
{
	spdlog::info("Initiallizing Server: Creating Socket...");

	m_socket = new SocketBase(ip, port, AF_INET, SOCK_STREAM, 0);
}

webserver::Server::~Server()
{
}

void webserver::Server::Start()
{
	spdlog::info("Starting Server");

	m_socket->StartListening();
	
	m_Running = true;

	//main server loop
	while (m_Running)
	{
		m_socket->GetConnection();



		spdlog::info("End of Server Loop");
	}

}
