#include "HttpResponse.h"

webserver::HttpResponse::HttpResponse()
{

}

void webserver::HttpResponse::SetProtocol(const char* protocol)
{
	m_Protocol = protocol;
}

void webserver::HttpResponse::SetStatus(unsigned int status)
{
	m_StatusCode = status;

	auto mapIterator = m_StatusMap.find(status);

	if (mapIterator != m_StatusMap.end()) {
		std::strncpy(m_StatusText, mapIterator->second, STATUS_TEXT_LENGTH);
	}
	else {
		std::strncpy(m_StatusText, "Unknown", STATUS_TEXT_LENGTH);
	}
}

std::string webserver::HttpResponse::ToString() const
{
	std::ostringstream response;

	//add header to response
	response << m_Protocol << " " << m_StatusCode << " " << m_StatusText << "\r\n";
	response << "\r\n";

	return response.str(); 
}
