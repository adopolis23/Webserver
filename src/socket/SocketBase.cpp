#include "SocketBase.h"

webserver::SocketBase::SocketBase(const char* ipAddress, int port, int domain, int type, int protocol) :
	m_ipAddress(ipAddress), m_port(port), m_domain(domain), m_type(type), m_protocol(protocol)
{

	m_connectionCapacity = 10;

	#ifdef PLATFORM_WINDOWS
		if (WSAStartup(MAKEWORD(2, 0), &m_wsaData) != 0)
		{
			spdlog::error("WSA Startup Failed");
			exit(1);
		}
	#endif

	//try to create main listener socket
	//socket(AF_INET, SOCK_STREAM, 0);
	m_socket = socket(domain, type, protocol);

	if (m_socket < 0)
	{
		spdlog::error("Failed to create Listener Socket");
		exit(1);
	}
	else
	{
		spdlog::info("Listener Socket Created");
	}
	
	memset(&m_socketAddress, 0, sizeof(m_socketAddress));
	m_socketAddress.sin_family = AF_INET;
	m_socketAddress.sin_port = htons(m_port);
	m_socketAddress.sin_addr.s_addr = inet_addr(m_ipAddress);

	if (bind(m_socket, (sockaddr*)&m_socketAddress, sizeof(m_socketAddress)) < 0)
	{
		spdlog::error("Cannot connect socket to address");
		exit(1);
	}
	else
	{
		spdlog::info("Socket bound to address {} on port {}", inet_ntoa(m_socketAddress.sin_addr), ntohs(m_socketAddress.sin_port));
	}
}

webserver::SocketBase::~SocketBase()
{
	#ifdef PLATFORM_WINDOWS
		closesocket(m_socket);
		WSACleanup();
		exit(0);
	#else
		close(m_socket);
		exit(0);
	#endif
}

void webserver::SocketBase::StartListening()
{
	if (listen(m_socket, 20) < 0)
	{
		spdlog::error("Socket Listen Failed");
		exit(1);
	}
	else
	{
		spdlog::info("Listening on {} PORT: {}", inet_ntoa(m_socketAddress.sin_addr), ntohs(m_socketAddress.sin_port));
	}

	return 0;
}
