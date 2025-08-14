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
		void CloseSocket(int sock);

	private:

		SocketBase* m_socket;
		int m_Connection;
		bool m_Running;

		const int BUFFER_SIZE = 4096;
	};

}