#ifdef _WIN32
    #pragma once 
    #include "http_server.hpp"
    #include "utility.hpp"
    #include <winsock2.h>
    
    namespace http
    {
        class WindowsHttpServer : public HttpServer
        {
        public:
            WindowsHttpServer(const std::string& ip_address = "127.0.0.1", int port = 8000);
            virtual ~WindowsHttpServer() override;
            
            virtual void startListen() override;
            virtual void acceptConnection(SOCKET& new_socket) override;
            virtual void sendResponse() override;

        
            private:
            virtual int startServer() override;
            virtual void closeServer() override;
        };
    }
#endif