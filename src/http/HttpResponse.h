#pragma once

namespace webserver
{

	#define PROTOCOL_LENGTH 16

	class HttpResponse
	{

	public:
		HttpResponse();
		~HttpResponse() = default;

	private:

		char m_Protocol[PROTOCOL_LENGTH + 1];

	};

}


