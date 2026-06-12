#ifdef _WIN32
#include "windows_tcp_server.hpp"
#include <format>
namespace http
{
    WindowsTcpServer::WindowsTcpServer(const std::string& ip_address, int port):
        TcpServer(ip_address, port)
    {
        socket_address_length_ = sizeof(socket_address_);
        socket_ = INVALID_SOCKET;
        new_socket_ = INVALID_SOCKET;
        socket_address_.sin_family = AF_INET;
        socket_address_.sin_port = htons(port_);
        INT result = InetPtonA(AF_INET, ip_address_.c_str(), &socket_address_.sin_addr);

        if (result <= 0)
        {
            if (result == 0)
            {
                exitWithError("Invalid IP address format: " + ip_address_);
            }
            else
            {
                exitWithError(std::format("Network error: {}", WSAGetLastError()));
            }
            closeServer();
        }
        if (startServer() != 0)
        {
            log(std::format("Failed to start server with PORT: {}", ntohs(socket_address_.sin_port)));
        }
    }

    WindowsTcpServer::~WindowsTcpServer()
    {
        closeServer();
    }

    void WindowsTcpServer::startListen()
    {
        if(listen(socket_, 20) == SOCKET_ERROR)
        {
            http::exitWithError("Listen failed with error: " + std::to_string(WSAGetLastError()));
            closeServer();
        }
        
        log(std::format("\n*** Listening on ADDRESS: {} PORT: {} ***\n\n", ip_address_, port_));

        while (true)
        {
            log("====== Waiting for a new connection ======\n\n\n");
            acceptConnection(new_socket_);

            char buffer[BUFFER_SIZE] = {0};

            int bytesReceived = recv(new_socket_, buffer, BUFFER_SIZE, 0);


            if (bytesReceived < 0)
            {
                http::exitWithError("Failed to receive data: " + std::to_string(WSAGetLastError()));
                closeServer();
            }
            log("------ Received Request from client ------\n\n");

            sendResponse();
            closesocket(new_socket_);
        }
    }

    void WindowsTcpServer::acceptConnection(SOCKET& new_socket)
    {
        new_socket = accept(socket_, (struct sockaddr*)&socket_address_, &socket_address_length_);
        
        if(new_socket == INVALID_SOCKET)
        {
            http::exitWithError(std::format("Accept failed with error: {}", WSAGetLastError()));
            closeServer();
        }
    }

    void WindowsTcpServer::sendResponse()
    {
        long bytesSent = send(new_socket_, buildResponse().c_str(), static_cast<int>(buildResponse().length()), 0);

        if(bytesSent == server_message_.size())
        {
            log("------ Response sent to client successfully -----\n\n");
        }
        else
        {
            log("Error sending response to client: " + std::to_string(WSAGetLastError()));
        }
    }


    int WindowsTcpServer::startServer()
    {
        int iResult = WSAStartup(MAKEWORD(2, 0), &wsaData_);
        if (iResult != 0)
        {
            exitWithError("WSAStartup failed with error: " + std::to_string(iResult));
            return 1;
        }
        log("Winsock initialized successfully");

        // Create a socket
        socket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (socket_ == INVALID_SOCKET)
        {
            exitWithError("Failed to create socket: " + std::to_string(WSAGetLastError()));
            WSACleanup();
            return 1;
        }

        if (bind(socket_, (struct sockaddr *)&socket_address_, socket_address_length_) == SOCKET_ERROR)
        {
            exitWithError("Cannot bind socket to address: " + std::to_string(WSAGetLastError()));
            closesocket(socket_);
            WSACleanup();
            return 1;
        }

        log("Socket created and bound successfully");
        return 0;
    }

    void WindowsTcpServer::closeServer()
    {
        if (socket_ != INVALID_SOCKET)
        {
            closesocket(socket_);
            socket_ = INVALID_SOCKET;
        }
        if (new_socket_ != INVALID_SOCKET)
        {
            closesocket(new_socket_);
            new_socket_ = INVALID_SOCKET;
        }
        WSACleanup();
        log("Sockets closed and Winsock cleaned up successfully");
    }
}
#endif