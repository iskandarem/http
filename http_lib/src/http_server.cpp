#include "http_server.hpp"
#include "utility.hpp"
#ifdef __linux__
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif
#include <cstring>
#include <format>
#include <iostream>
#include "http_request.hpp"
#include "http_response.hpp"
namespace http
{
    HttpServer::HttpServer(const std::string& ip_address, int port):
    ip_address_(ip_address),
    port_(port),
    incoming_message_{},
    socket_address_length_{},
    socket_{},
    new_socket_{}
    #ifdef _WIN32
    , wsaData_{}
    #endif
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

    void HttpServer::startListen()
    {
        if(listen(socket_, 20) < 0)
        {
            exitWithError("Socket listen failed");
        }
        log(std::format("\n*** Listening on  http://{}:{} ***\n\n", inet_ntoa(socket_address_.sin_addr), ntohs(socket_address_.sin_port)));

        int bytesReceived{};
        while (true)
        {
            log("====== Waiting for a new connection ======\n\n\n");
            acceptConnection(new_socket_);

            char* buffer = new char[BUFFER_SIZE];
            bytesReceived = read(new_socket_, buffer, BUFFER_SIZE);
            HttpRequest req = HttpRequest::parse(buffer);
            if(bytesReceived < 0)
            {
                exitWithError("failed to read bytes from client socket connection");
            }

            log("------ Received Request from client ------\n\n");
			auto response = router_.dispatch(req);
            sendResponse(response);
            close(new_socket_);
        }
        
    }

    void HttpServer::acceptConnection(int &new_socket)
    {
        new_socket = accept(socket_, (sockaddr *)&socket_address_, &socket_address_length_);
        if (new_socket < 0)
        {
            
            exitWithError(std::format("Server failed to accept incoming connection from ADDRESS: {0}; PORT: {0}", 
                inet_ntoa(socket_address_.sin_addr), ntohs(socket_address_.sin_port)));
        }
    }

    void HttpServer::sendResponse(const HttpResponse& response)
    {
        long bytesSent;
        auto raw_response = response.serialize();
        bytesSent = write(new_socket_, raw_response.c_str(), raw_response.size());

        if (bytesSent == raw_response.size())
        {
            log("------ Server Response sent to client ------\n\n");
        }
        else
        {
            log("Error sending response to client");
        }
    }

    int HttpServer::startServer()
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
        return 0;
    }

    void HttpServer::closeServer()
    {
        close(socket_);
        close(new_socket_);
        http::log("Sockets closed successfully");
    }

    void http::HttpServer::setController(std::unique_ptr<BaseController> controller)
    {
        controller_ = std::move(controller);
    }

    http::Router& http::HttpServer::router()
    {
        return router_;
    }
}


