#include "HttpResponse.h"

webserver::HttpResponse::HttpResponse(const char* rootFolder)
{
	m_rootFolder = rootFolder;
}

void webserver::HttpResponse::SetProtocol(const char* protocol)
{
	m_Protocol = protocol;
}

void webserver::HttpResponse::SetTarget(const char* target)
{
	m_Target = target;

	size_t target_length = m_Target.length();

	if (target_length > 0 && m_Target[target_length - 1] == '/')
	{
		//target ends with a / and we assume they want /index.html
		const char* filename = "index.html";
		
		m_Target = m_Target + filename;


		//add the correct content type
		AddHeader("Content-Type", m_GetContentType(m_Target));

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

std::string webserver::HttpResponse::ToString() const
{
	std::string full_target = m_rootFolder + m_Target;
	spdlog::info("Full path of requested file: {}", full_target);

	//create body
	std::ifstream file(full_target, std::ios::binary);
	if (!file.is_open()) {
		spdlog::error("Requested file is not found.");

		std::string notFound = 
			"HTTP/1.1 404 Not Found\r\n"
			"Content-Type: text/plain\r\n"
			"Content-Length: 13\r\n"
			"\r\n"
			"404 Not Found";
		return notFound.c_str();
	}

	//read file into buffer
    std::ostringstream bodyStream;
    bodyStream << file.rdbuf();


	//create header
	std::ostringstream headerStream;

	headerStream << m_Protocol << " " << m_StatusCode << " " << m_StatusText << "\r\n";

	for (auto item : m_Headers)
	{
		headerStream << item.first << ":" << item.second << "\r\n";
	}
	headerStream << "Content-Length: " << bodyStream.str().size() << "\r\n";
	headerStream << "\r\n";

	spdlog::info("Header Created: {}", headerStream.str());


	//create full response
	std::string response;
	response = headerStream.str() + bodyStream.str();

	return response; 
}


void webserver::HttpResponse::AddHeader(std::string name, std::string value)
{
	m_Headers[name] = value;
}

std::string webserver::HttpResponse::m_GetContentType(const std::string& path)
{

	if (path.ends_with(".html")) return "text/html";
    if (path.ends_with(".css"))  return "text/css";
    if (path.ends_with(".js"))   return "application/javascript";
    if (path.ends_with(".png"))  return "image/png";
    if (path.ends_with(".jpg") || path.ends_with(".jpeg")) return "image/jpeg";
    return "application/octet-stream";

}
