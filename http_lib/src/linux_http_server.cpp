#ifdef __linux__
#include "linux_http_server.hpp"
#include "utility.hpp"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <format>
#include <iostream>
#include "http_request.hpp"

namespace http
{
    LinuxHttpServer::LinuxHttpServer(const std::string& ip_address, int port): 
        HttpServer(ip_address, port)
    {
        socket_address_length_ = sizeof(socket_address_);
        socket_address_.sin_family = AF_INET;
        socket_address_.sin_port = htons(port_);
        socket_address_.sin_addr.s_addr = inet_addr(ip_address_.c_str());

        if (startServer() != 0)
        {
            log(std::format("Failed to start server with PORT: {}", ntohs(socket_address_.sin_port)));
        }
    }

    void LinuxHttpServer::startListen()
    {
        if(listen(socket_, 20) < 0)
        {
            exitWithError("Socket listen failed");
        }
        log(std::format("\n*** Listening on ADDRESS: {} PORT: {} ***\n\n", inet_ntoa(socket_address_.sin_addr), ntohs(socket_address_.sin_port)));

        int bytesReceived{};
        while (true)
        {
            log("====== Waiting for a new connection ======\n\n\n");
            acceptConnection(new_socket_);

            char* buffer = new char[BUFFER_SIZE];
            bytesReceived = read(new_socket_, buffer, BUFFER_SIZE);
            HttpRequest req = HttpRequest::parse(buffer);
            std::cout << buffer << std::endl;
            std::cout << req.to_string() << std::endl;
            if(bytesReceived < 0)
            {
                exitWithError("failed to read bytes from client socket connection");
            }

            log("------ Received Request from client ------\n\n");

            sendResponse();
            close(new_socket_);
        }
        
    }

    void LinuxHttpServer::acceptConnection(int &new_socket)
    {
        new_socket = accept(socket_, (sockaddr *)&socket_address_, &socket_address_length_);
        if (new_socket < 0)
        {
            
            exitWithError(std::format("Server failed to accept incoming connection from ADDRESS: {0}; PORT: {0}", 
                inet_ntoa(socket_address_.sin_addr), ntohs(socket_address_.sin_port)));
        }
    }

    void LinuxHttpServer::sendResponse()
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

    int LinuxHttpServer::startServer()
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
        log(std::format("\n*** Listening on ADDRESS: {} PORT: {} ***\n\n", inet_ntoa(socket_address_.sin_addr), ntohs(socket_address_.sin_port)));
        return 0;
    }

    void LinuxHttpServer::closeServer()
    {
        close(socket_);
        close(new_socket_);
        http::log("Sockets closed successfully");
    }
}

#endif