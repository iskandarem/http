#include "linux_tcp_server.hpp"


#ifdef __linux__

#include "utility.hpp"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>


namespace http
{
    LinuxTcpServer::LinuxTcpServer(const std::string& ip_address, int port): 
        TcpServer(ip_address, port),
        socket_{},
        new_socket_{}
    {
        startServer();
    }

    int LinuxTcpServer::startServer()
    {
        socket_ = socket(AF_INET, SOCK_STREAM, 0);
        if (socket_ < 0)
        {
            http::exitWithError("Failed to create socket");
            return 1;
        }
        http::log("Socket created successfully");
        return 0;
    }

    void LinuxTcpServer::closeServer()
    {
        close(socket_);
        close(new_socket_);
        http::log("Sockets closed successfully");
        exit(0);
    }
}

#endif