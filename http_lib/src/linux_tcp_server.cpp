#include "linux_tcp_server.hpp"


#ifdef __linux__

#include "utility.hpp"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sstream>
#include <cstring>

namespace http
{
    LinuxTcpServer::LinuxTcpServer(const std::string& ip_address, int port): 
        TcpServer(ip_address, port),
        socket_{},
        new_socket_{}
    {
        socket_address_length_ = sizeof(socket_address_);
        socket_address_.sin_family = AF_INET;
        socket_address_.sin_port = htons(port_);
        socket_address_.sin_addr.s_addr = inet_addr(ip_address_.c_str());

        if (startServer() != 0)
        {
            std::ostringstream ss;
            ss << "Failed to start server with PORT: " << ntohs(socket_address_.sin_port);
            log(ss.str());
        }
    }

    void LinuxTcpServer::startListen()
    {
        if(listen(socket_, 20) < 0)
        {
            exitWithError("Socket listen failed");
        }

        std::ostringstream oss;
        oss << "\n*** Listening on ADDRESS: " << inet_ntoa(socket_address_.sin_addr) << " PORT: " << ntohs(socket_address_.sin_port) << " ***\n\n";
        log(oss.str());

        int bytesReceived{};
        while (true)
        {
            log("====== Waiting for a new connection ======\n\n\n");
            acceptConnection(new_socket_);

            char buffer[BUFFER_SIZE];
            std::memset(buffer, 0, BUFFER_SIZE);
            bytesReceived = read(new_socket_, buffer, BUFFER_SIZE);
            if(bytesReceived < 0)
            {
                exitWithError("failed to read bytes from client socket connection");
            }

            log("------ Received Request from client ------\n\n");

            sendResponse();
            close(new_socket_);
        }
        
    }

    void LinuxTcpServer::acceptConnection(int &new_socket)
    {
        new_socket = accept(socket_, (sockaddr *)&socket_address_, &socket_address_length_);
        if (new_socket < 0)
        {
            std::ostringstream ss;
            ss << "Server failed to accept incoming connection from ADDRESS: " << inet_ntoa(socket_address_.sin_addr) 
            << "; PORT: " << ntohs(socket_address_.sin_port);
            exitWithError(ss.str());
        }
    }

    void LinuxTcpServer::sendResponse()
    {
        long bytesSent;

        bytesSent = write(new_socket_, server_message_.c_str(), server_message_.size());

        if (bytesSent == server_message_.size())
        {
            log("------ Server Response sent to client ------\n\n");
        }
        else
        {
            log("Error sending response to client");
        }
    }

    int LinuxTcpServer::startServer()
    {
        socket_ = socket(AF_INET, SOCK_STREAM, 0);
        if (socket_ < 0)
        {
            http::exitWithError("Failed to create socket");
            return 1;
        }
        if(bind(socket_, (sockaddr *)&socket_address_, socket_address_length_) < 0)
        {
            exitWithError("Cannot connect socket to address");
            return 1;
        }
        log("Socket created successfully");
        std::ostringstream ss;
        ss << "\n*** Listening on ADDRESS: " 
            << inet_ntoa(socket_address_.sin_addr) 
            << " PORT: " << ntohs(socket_address_.sin_port) 
            << " ***\n\n";
        log(ss.str());
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