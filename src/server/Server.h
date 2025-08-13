#pragma once

#include "socket/SocketBase.h"
#include <spdlog/spdlog.h>

namespace webserver
{

	class Server
	{
	public:

		Server(const char* ip, unsigned int port);
		~Server();

		void Start();

	private:

		SocketBase* m_socket;
		bool m_Running;

	};

}