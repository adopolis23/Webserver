#pragma once

#include <queue>
#include <thread>

#include <spdlog/spdlog.h>
#include "socket/SocketListener.h"
#include "http/HttpRequest.h"
#include "http/HttpResponse.h"

#define BUFFER_SIZE 4096

#ifdef PLATFORM_WINDOWS
	#define close closesocket
#endif

typedef int Connection;

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

        // Thread to deal with accepting connection and placing in queue
        std::thread m_AcceptorThread;

        // Thread to deal with proccessing connections that have been accepted and are in queue
        std::thread m_WorkerThread;

        // queue to hold accepted connections
        std::queue<Connection> m_ConnectionQueue;

        void AcceptorThread();
        void WorkerThread();

		SocketListener* m_Socket;
		int m_Connection;

        std::atomic<bool> m_Running;

	};

}
