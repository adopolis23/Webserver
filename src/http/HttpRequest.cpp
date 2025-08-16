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
	char* saveptr_line, saveptr_space;

	strcpy(mutable_request, rawRequest);

	const char deliminator[] = "\r\n";

	char* token = strtok_r(mutable_request, deliminator, &saveptr_line);

	if (token == NULL)
	{
		spdlog::warn("No CRLF found in request.");
	}

	while (token != NULL)
	{
		spdlog::info("Line: {}", token);


	
		//get next token
		token = strtok_r(NULL, deliminator, &saveptr_line);
	}

}
