#ifdef _WIN32
    #pragma once 
    #include "tcp_server.hpp"
    #include "utility.hpp"
    #include <winsock2.h>
    
    namespace http
    {
        class WindowsTcpServer : public TcpServer
        {
        public:
            WindowsTcpServer(const std::string& ip_address = "127.0.0.1", int port = 8000);
            virtual ~WindowsTcpServer() override;
            
            virtual void startListen() override;
            virtual void acceptConnection(SOCKET& new_socket) override;
            virtual void sendResponse() override;

        
            private:
            virtual int startServer() override;
            virtual void closeServer() override;
        };
    }
#endif