#pragma once
#include <string>

namespace http
{
    class TcpServer
    {
    public:
        TcpServer(const std::string& ip_address = "127.0.0.1", int port = 8000);
        virtual ~TcpServer() = default;
    
    protected:
        std::string ip_address_;
        int port_;
        long incoming_message_;
        // struct SockAddrIn server_address_;
        // struct sockaddr_in server_address_;
        unsigned int socket_address_length_;
        std::string server_message_;

        std::string buildResponse();
        
        virtual int startServer() = 0;
        virtual void closeServer() = 0;
    };
}