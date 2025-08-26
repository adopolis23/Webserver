#pragma once
#include <string>
#include <unordered_map>
#include "spdlog/spdlog.h"

namespace webserver
{

	#define STATUS_TEXT_LENGTH 32
	#define TARGET_LENGTH 128

	class HttpResponse
	{

	public:
		HttpResponse();
		~HttpResponse() = default;

		void SetProtocol(const char* protocol);
		void SetStatus(unsigned int status);
		void SetTarget(const char* target);

		void AddHeader(std::string name, std::string value);

		const char* ToString() const; // build full HTTP response header

	private:

		std::string m_GetContentType(const std::string& path);

		std::string m_Protocol;
		unsigned int m_StatusCode;
		char m_StatusText[STATUS_TEXT_LENGTH + 1] = {};
		char m_Target[TARGET_LENGTH + 1] = {};

		std::map<std::string, std::string> m_Headers;
		
		const std::unordered_map<unsigned int, const char*> m_StatusMap = {
			{200, "OK"},
			{201, "Created"},
			{204, "No Content"},
			{301, "Moved Permanently"},
			{302, "Found"},
			{400, "Bad Request"},
			{401, "Unauthorized"},
			{403, "Forbidden"},
			{404, "Not Found"},
			{500, "Internal Server Error"},
			{501, "Not Implemented"},
			{503, "Service Unavailable"}
		};


	};

}


