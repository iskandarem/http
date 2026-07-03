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
#include "http_response.hpp"
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
        HttpResponse response{};
        response.setVersion( "HTTP/1.1" );
        response.setStatus(OK);
        response.setBody(
                    R"(<!DOCTYPE html>
            <html lang="en">
            <head>
                <meta charset="UTF-8">
                <meta name="viewport" content="width=device-width, initial-scale=1.0">
                <title>Welcome to http_lib</title>
                <style>
                    :root {
                        --bg-color: #0f172a;
                        --card-bg: #1e293b;
                        --text-main: #f8fafc;
                        --text-muted: #94a3b8;
                        --accent: #38bdf8;
                    }
                    body {
                        font-family: system-ui, -apple-system, sans-serif;
                        background-color: var(--bg-color);
                        color: var(--text-main);
                        display: flex;
                        justify-content: center;
                        align-items: center;
                        min-height: 100vh;
                        margin: 0;
                    }
                    .container {
                        background-color: var(--card-bg);
                        padding: 2.5rem;
                        border-radius: 12px;
                        box-shadow: 0 10px 25px -5px rgba(0, 0, 0, 0.3);
                        text-align: center;
                        max-width: 450px;
                        width: 90%;
                        border: 1px solid #334155;
                    }
                    h1 {
                        color: var(--accent);
                        margin-top: 0;
                        font-size: 2.25rem;
                    }
                    p {
                        color: var(--text-muted);
                        line-height: 1.6;
                        font-size: 1.1rem;
                    }
                    .status-badge {
                        display: inline-block;
                        background-color: #065f46;
                        color: #34d399;
                        padding: 0.25rem 0.75rem;
                        border-radius: 9999px;
                        font-size: 0.875rem;
                        font-weight: 600;
                        margin-bottom: 1rem;
                    }
                </style>
            </head>
            <body>
                <div class="container">
                    <div class="status-badge">Server Online</div>
                    <h1>Welcome to http_lib</h1>
                    <p>Your minimalist C++ HTTP server is running successfully and serving structured HTML content over TCP sockets.</p>
                </div>
            </body>
            </html>)"
        );
        response.Headers.insert(std::pair<std::string, std::string>("content-length", std::to_string(response.getBody().size())));
        response.Headers.insert(std::pair<std::string, std::string>("content-type", "text/html"));
        response.Headers.insert(std::pair<std::string, std::string>("connection", "close"));

        auto raw_response = response.to_string();
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