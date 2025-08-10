#include "SocketBase.h"

webserver::SocketBase::SocketBase(int domain, int type, int protocol) :
	m_domain(domain), m_type(type), m_protocol(protocol)
{

	if (g_Platform == WINDOWS)
	{
		if (WSAStartup(MAKEWORD(2, 0), &m_wsaData) != 0)
		{
			perror("WSAStartup failed");
		}
	}

	//try to create main listener socket
	//socket(AF_INET, SOCK_STREAM, 0);
	m_socket = socket(domain, type, protocol);

	if (m_socket < 0)
	{
		perror("Failed to create Listener Socket");
	}
	else
	{
		std::cout << "Listener Socket Created" << std::endl;
	}
	

}

webserver::SocketBase::~SocketBase()
{
}
