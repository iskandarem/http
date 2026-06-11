#pragma once 
#include "tcp_server.hpp"
#include "utility.hpp"

#ifdef _WIN32
    #error "This header is for Windows only. Please include tcp_server.hpp instead."   
    #include <winsock2.h>
    
    namespace http
    {
        class WindowsTcpServer : public TcpServer
        {
            public:
            WindowsTcpServer(const std::string& ip_address = "127.0.0.1", int port = 8000);
            ~WindowsTcpServer() override = default;
            
            virtual int startServer() override;
            virtual void closeServer() override;
            private:
            SOCKET socket_;
            SOCKET new_socket_;
            WSADATA wsaData_;
        };
    }
#endif