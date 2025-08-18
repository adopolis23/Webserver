#pragma once

#include "socket/SocketListener.h"
#include <spdlog/spdlog.h>
#include "http/HttpRequest.h"
#include "http/HttpResponse.h"

#define BUFFER_SIZE 4096

#ifdef PLATFORM_WINDOWS
	#define close closesocket
#endif

namespace webserver
{

	class Server
	{
	public:

		Server(const char* rootFolder, const char* ip, unsigned int port);
		~Server();

		void Start();
		void CloseSocket(int sock);

	private:

		const char* m_RootFolder;

		SocketListener* m_Socket;
		int m_Connection;
		bool m_Running;

	};

}