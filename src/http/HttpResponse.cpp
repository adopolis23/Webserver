#include "HttpResponse.h"

webserver::HttpResponse::HttpResponse()
{

}

void webserver::HttpResponse::SetProtocol(const char* protocol)
{
	m_Protocol = protocol;
}

void webserver::HttpResponse::SetTarget(const char* target)
{
	strncpy(m_Target, target, sizeof(m_Target));

	size_t target_length = std::strlen(m_Target);

	if (target_length > 0 && m_Target[target_length - 1] == '/')
	{
		//target ends with a / and we assume they want /index.html
		const char* filename = "index.html";

		if (std::strlen(filename) + target_length < TARGET_LENGTH)
		{

		}

	}
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

const char* webserver::HttpResponse::ToString() const
{
	std::ostringstream response;

	//add header to response
	response << m_Protocol << " " << m_StatusCode << " " << m_StatusText << "\r\n";
	response << "\r\n";

	return response.str().c_str(); 
}


void webserver::HttpResponse::AddHeader(std::string name, std::string value)
{
	m_Headers.insert(name, value);
}
