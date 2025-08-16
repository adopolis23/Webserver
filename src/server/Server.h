#pragma once

#include "socket/SocketBase.h"
#include <spdlog/spdlog.h>

#define BUFFER_SIZE 4096

namespace webserver
{

	class Server
	{
	public:

		Server(const char* ip, unsigned int port);
		~Server();

		void Start();
		void CloseSocket(int sock);

	private:

		SocketBase* m_socket;
		int m_Connection;
		bool m_Running;

	};

}