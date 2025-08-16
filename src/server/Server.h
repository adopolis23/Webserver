#pragma once

#include "socket/SocketListener.h"
#include <spdlog/spdlog.h>
#include "http/HttpRequest.h"

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

		SocketListener* m_socket;
		int m_Connection;
		bool m_Running;

	};

}