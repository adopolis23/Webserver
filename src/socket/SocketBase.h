#pragma once

#include "../Core.h"
#include <iostream>

#ifdef PLATFORM_WINDOWS
	#include <winsock2.h>
#else
	#include <sys/socket.h>
#endif


namespace webserver
{

	class SocketBase
	{
	public:
		SocketBase(int domain, int type, int protocol);
		~SocketBase();

	private:
		unsigned int m_socket;
		int m_domain;
		int m_type;
		int m_protocol;

		WSADATA m_wsaData;


	};

}


