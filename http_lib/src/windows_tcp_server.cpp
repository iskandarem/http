#include "windows_tcp_server.hpp"

#ifdef _WIN32
    #error "This source file is for Windows only. Please include tcp_server.cpp instead."
namespace http
{
    WindowsTcpServer::WindowsTcpServer(const std::string& ip_address, int port):
        TcpServer(ip_address, port),
        socket_{},
        new_socket_{}
    {
        startServer();
    }

    int WindowsTcpServer::startServer()
    {
        int iResult = WSAStartup(MAKEWORD(2, 0), &wsaData);
        if (iResult != 0)
        {
            http::exitWithError("WSAStartup failed with error: " + std::to_string(iResult));
            return 1;
        }
        http::log("Winsock initialized successfully");

        // Create a socket
        socket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (socket_ < 0)
        {
            http::exitWithError("Failed to create socket: " + std::to_string(WSAGetLastError()));
            WSACleanup();
            return 1;
        }
        http::log("Socket created successfully");
        return 0;
    }

    void WindowsTcpServer::closeServer()
    {
        closesocket(socket_);
        closesocket(new_socket_);
        WSACleanup();
        http::log("Sockets closed and Winsock cleaned up successfully");
        exit(0);
    }
}
#endif