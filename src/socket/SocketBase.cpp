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
		spdlog::error("Failed to create Listener Socket: {}", m_socket);
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

	int bind_error_code = bind(m_socket, (sockaddr*)&m_socketAddress, sizeof(m_socketAddress));
	if (bind_error_code < 0)
	{
		#ifdef PLATFORM_WINDOWS
			int errorCode = WSAGetLastError();
			spdlog::error("Cannot bind socket: {} ({})", errorCode, GetWSAErrorMessage(errorCode));
		#else
			spdlog::error("errno = {} ({})\n", errno, strerror(errno));
			spdlog::error("Cannot bind socket to address: {}", bind_error_code);
		#endif

		exit(1);


	}
	else
	{
		spdlog::info("Socket bound to address {} on port {}", inet_ntoa(m_socketAddress.sin_addr), ntohs(m_socketAddress.sin_port));
	}

	m_socketAddress_len = sizeof(m_socketAddress);
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
	if (listen(m_socket, m_connectionCapacity) < 0)
	{
		spdlog::error("Socket Listen Failed");
		exit(1);
	}
	else
	{
		spdlog::info("Listening on {} PORT: {}", inet_ntoa(m_socketAddress.sin_addr), ntohs(m_socketAddress.sin_port));
	}

}

std::string webserver::SocketBase::GetWSAErrorMessage(int errorCode)
{
	#ifdef PLATFORM_WINDOWS
		char* msgBuf = nullptr;
		FormatMessageA(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			nullptr,
			errorCode,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPSTR)&msgBuf,
			0,
			nullptr);

		std::string message = msgBuf ? msgBuf : "Unknown error";
		LocalFree(msgBuf);
		return message;
	#else
		return "Function not implemented on Linux.";
	#endif
}

//this function is blocking, accept will wait for a connection.
int webserver::SocketBase::GetConnection()
{
	spdlog::info("Checking for incomming connections...");

	int new_connection = accept(m_socket, (sockaddr *)&m_socketAddress, &m_socketAddress_len);
	if (new_connection != INVALID_SOCKET)
	{
		spdlog::info("Accepted Connection on {} PORT: {}", inet_ntoa(m_socketAddress.sin_addr), ntohs(m_socketAddress.sin_port));
		return new_connection;
	}
	else
	{
		spdlog::warn("'Accept' Returned {}", new_connection);

		#ifdef PLATFORM_WINDOWS
			int errorCode = WSAGetLastError();
			spdlog::error("Cannot bind socket: {} ({})", errorCode, GetWSAErrorMessage(errorCode));
		#else
			spdlog::error("errno = {} ({})\n", errno, strerror(errno));
			spdlog::error("Cannot bind socket to address: {}", bind_error_code);
		#endif

			exit(1);
	}

	return 0;
}