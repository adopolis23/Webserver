#pragma once

#include "socket/SocketBase.h"

namespace webserver
{

	class Server
	{
	public:

		Server(const char* ip, unsigned int port);
		~Server();

	private:

		SocketBase m_socket;

	};

}