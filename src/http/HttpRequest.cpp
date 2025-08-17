#include "HttpRequest.h"

webserver::HttpRequest::HttpRequest(const char* rawRequest)
{
	m_Header = (HttpHeader*) malloc(sizeof(HttpHeader));

	ParseRequest(rawRequest);

}

webserver::HttpRequest::~HttpRequest()
{
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

	char* tokenSpace = strtok_r(mutable_request, space, &saveptr_space);
	strncpy(m_Header->Method, tokenSpace, METHOD_LENGTH);
	m_Header->Method[METHOD_LENGTH] = '\0';

	tokenSpace = strtok_r(NULL, space, &saveptr_space);
	strncpy(m_Header->RequestTarget, tokenSpace, REQUEST_TARGET_LENGTH);
	m_Header->RequestTarget[REQUEST_TARGET_LENGTH] = '\0';

}

const webserver::HttpHeader* webserver::HttpRequest::GetHeader()
{
	return m_Header;
}
