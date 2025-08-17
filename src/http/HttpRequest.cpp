#include "HttpRequest.h"

webserver::HttpRequest::HttpRequest(const char* rawRequest)
{
	ParseRequest(rawRequest);
}


void webserver::HttpRequest::ParseRequest(const char* rawRequest)
{
	char mutable_request[4096]; 
	mutable_request[4096 - 1] = '\0';
	char* saveptr_line;
	char* saveptr_space;

	strcpy(mutable_request, rawRequest);

	const char deliminator[] = "\r\n";
	const char space[] = " ";

	char* tokenLine = strtok_r(mutable_request, deliminator, &saveptr_line);

	if (tokenLine == NULL)
	{
		spdlog::warn("No CRLF found in request.");
	}

	//get method
	char* tokenSpace = strtok_r(mutable_request, space, &saveptr_space);
	if (tokenSpace) strncpy(m_Method, tokenSpace, METHOD_LENGTH);
	

	//get request target
	tokenSpace = strtok_r(NULL, space, &saveptr_space);
	if (tokenSpace) strncpy(m_RequestTarget, tokenSpace, REQUEST_TARGET_LENGTH);
	

	//get protocol
	tokenSpace = strtok_r(NULL, space, &saveptr_space);
	if (tokenSpace) strncpy(m_Protocol, tokenSpace, PROTOCOL_LENGTH);
	

}






const char* webserver::HttpRequest::GetMethod() const
{
	return m_Method;
}

const char* webserver::HttpRequest::GetRequestTarget() const
{
	return m_RequestTarget;
}

const char* webserver::HttpRequest::GetProtocol() const
{
	return m_Protocol;
}
