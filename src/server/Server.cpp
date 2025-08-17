#include "Server.h"

webserver::Server::Server(const char* rootFolder, const char* ip, unsigned int port)
: m_Running(false), m_Connection(NULL)
{
	spdlog::info("Initiallizing Server");


	spdlog::info("Creating Socket");
	m_Socket = new SocketListener(ip, port, AF_INET, SOCK_STREAM, 0);
}

webserver::Server::~Server()
{
}

void webserver::Server::CloseSocket(int sock)
{
	#ifdef PLATFORM_WINDOWS
		closesocket(sock);
		//WSACleanup();
	#else
		close(sock);
	#endif
}

void webserver::Server::Start()
{
	spdlog::info("Starting Server");

	m_Socket->StartListening();	
	m_Running = true;

	//create buffer to store data and null terminate.
	char buffer[BUFFER_SIZE] = {0};
	buffer[BUFFER_SIZE-1] = '\0';

	int bytesRecv = 0;

	//main server loop
	while (m_Running)
	{
		m_Connection = m_Socket->GetConnection();

		//read from socket
		#ifdef PLATFORM_WINDOWS
			bytesRecv = recv(m_Connection, buffer, BUFFER_SIZE, 0);
		#else
			bytesRecv = read(m_Connection, buffer, BUFFER_SIZE);
		#endif

		if (bytesRecv < 0)
		{
			spdlog::error("Failed to read from Socket");
			CloseSocket(m_Connection);
			continue;
		}
		
		//spdlog::info("Recieved From Socket: {}\n*******END OF BUFFER*********", (char *)buffer);
		

		//create the httpHeader object and parse request
		HttpRequest request(buffer);

		spdlog::info("Method: {}", request.GetMethod());
		spdlog::info("Request Target: {}", request.GetRequestTarget());
		spdlog::info("Request Protocol: {}\n", request.GetProtocol());




		CloseSocket(m_Connection);
	}

}
