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

void webserver::Server::CloseSocket(int sock)
{
	#ifdef PLATFORM_WINDOWS
		closesocket(sock);
		WSACleanup();
	#else
		close(sock);
	#endif
}

void webserver::Server::Start()
{
	spdlog::info("Starting Server");

	m_socket->StartListening();	
	m_Running = true;

	//create buffer to store data and null terminate.
	char buffer[BUFFER_SIZE] = {0};
	buffer[BUFFER_SIZE] = '\0';

	int bytesRecv = 0;

	//main server loop
	while (m_Running)
	{
		m_Connection = m_socket->GetConnection();

		//read from socket
		bytesRecv = read(m_Connection, buffer, BUFFER_SIZE);
		if (bytesRecv < 0)
		{
			spdlog::error("Failed to read from Socket");
		}
		else
		{
			spdlog::info("Recieved From Socket: {}", (char *)buffer);
			spdlog::info("\n********END OF BUFFER*******");
		}


		CloseSocket(m_Connection);
	}

}
