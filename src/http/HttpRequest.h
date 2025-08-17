
#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <spdlog/spdlog.h>

namespace webserver
{

    #ifdef PLATFORM_WINDOWS
        #define strtok_r strtok_s
    #endif
    
    struct HttpHeader
    {
        #define METHOD_LENGTH 4
        #define REQUEST_TARGET_LENGTH 1024
        #define PROTOCOL_LENGTH 16
        #define HOST_LENGTH 512

        char Method[METHOD_LENGTH + 1];
        char RequestTarget[REQUEST_TARGET_LENGTH + 1];
        char Protocol[PROTOCOL_LENGTH + 1];
        char Host[HOST_LENGTH + 1];
    };

    class HttpRequest
    {
        
    public:
        HttpRequest(const char* rawRequest);
        ~HttpRequest();

        void ParseRequest(const char* rawRequest);
        const HttpHeader* GetHeader() const { return m_Header; }

        const HttpHeader* GetHeader();

    private:
        HttpHeader* m_Header;
        
    };


}