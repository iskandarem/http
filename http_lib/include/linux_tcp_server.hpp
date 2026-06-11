#pragma once 
#include "tcp_server.hpp"

#ifdef __linux__

namespace http
{
    class LinuxTcpServer : public TcpServer
    {
    public:
        LinuxTcpServer(const std::string& ip_address = "127.0.0.1", int port = 8000);
        virtual ~LinuxTcpServer() override { closeServer(); };

        virtual int startServer() override;
        virtual void closeServer() override;
    private:
        int socket_;
        int new_socket_;
    };
}
#endif