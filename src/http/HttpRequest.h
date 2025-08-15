

namespace webserver
{
    
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
        HttpRequest();
        ~HttpRequest();

        void ParseRequest(const char* rawRequest);
        const HttpHeader* GetHeader() const { return m_Header; }

        
    private:
        HttpHeader* m_Header;
        
    };


}