#include "Server.h"

webserver::Server::Server(const char* rootFolder, const char* ip, unsigned int port)
: m_Running(false), m_Connection(NULL), m_RootFolder(rootFolder)
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
	close(sock);
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


		HttpResponse response;
		response.SetProtocol("HTTP/1.1");
		response.SetStatus(200);

		//todo need to fix what is going on in this line maybe maybe tostring return a c string
		int sent = send(m_Connection, response.ToString().c_str(), strlen(response.ToString().c_str()), 0);
		if (sent < 0) {
			spdlog::error("Send Error: {}", sent);
			exit(1);
		}


		CloseSocket(m_Connection);
	}

}
