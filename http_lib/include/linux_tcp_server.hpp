#pragma once 
#ifdef __linux__
#include "tcp_server.hpp"
#include <arpa/inet.h>
namespace http
{
    class LinuxTcpServer : public TcpServer
    {
    public:
        LinuxTcpServer(const std::string& ip_address = "127.0.0.1", int port = 8000);
        virtual ~LinuxTcpServer() override { closeServer(); };

        virtual void startListen() override;
        virtual void acceptConnection(int& new_socket) override; 
        virtual void sendResponse() override;
    private:
        int socket_;
        int new_socket_;
        struct sockaddr_in socket_address_;

        virtual int startServer() override;
        virtual void closeServer() override;
    };
}
#endif