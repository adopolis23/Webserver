
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
        char Method[4];
        char RequestTarget[1024];
        char Protocol[16];
        char Host[1024];
    };

    class HttpRequest
    {
        
    public:
        HttpRequest(const char* rawRequest);
        ~HttpRequest();

        void ParseRequest(const char* rawRequest);
        const HttpHeader* GetHeader() const { return m_Header; }

        
    private:
        HttpHeader* m_Header;
        
    };


}