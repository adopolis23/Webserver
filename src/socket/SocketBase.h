#pragma once

#include "../Core.h"
#include <iostream>
#include <spdlog/spdlog.h>
#include <string>
#include <queue>

#ifdef PLATFORM_WINDOWS
    #include <winsock2.h>
    #include <ws2tcpip.h>
#else
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <sys/socket.h>
#endif


namespace webserver
{

	class SocketBase
	{
	public:
		SocketBase(const char* ipAddress, int port, int domain, int type, int protocol);
		~SocketBase();

		void StartListening();
		int GetConnection();

		std::string GetWSAErrorMessage(int errorCode);

	private:
		unsigned int m_socket;
		int m_domain;
		int m_type;
		int m_protocol;
		int m_port;
		const char* m_ipAddress;

		int m_connectionCapacity;

		#ifdef PLATFORM_WINDOWS
			WSADATA m_wsaData;
		#endif

		struct sockaddr_in m_socketAddress;
		socklen_t m_socketAddress_len;


	};

}


