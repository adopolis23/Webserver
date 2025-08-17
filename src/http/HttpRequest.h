
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
    

    #define METHOD_LENGTH 4
    #define REQUEST_TARGET_LENGTH 512
    #define PROTOCOL_LENGTH 16


    class HttpRequest
    {
        
    public:
        HttpRequest(const char* rawRequest);
        ~HttpRequest() = default;

        void ParseRequest(const char* rawRequest);

        const char* GetMethod() const;
        const char* GetRequestTarget() const;
        const char* GetProtocol() const;

    private:
        char m_Method[METHOD_LENGTH + 1];
        char m_RequestTarget[REQUEST_TARGET_LENGTH + 1];
        char m_Protocol[PROTOCOL_LENGTH + 1];
        
    };


}