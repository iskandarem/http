#pragma once
#include <string>

#ifdef _WIN32
    #include<winsock2.h>
#endif

namespace http
{
    class TcpServer
    {
    public:
        TcpServer(const std::string& ip_address = "127.0.0.1", int port = 8000);
        virtual ~TcpServer() = default;

        virtual void startListen() = 0;

        #ifdef __linux__
            virtual void acceptConnection(int& new_socket) = 0;
        #elif _WIN32
            virtual void acceptConnection(SOCKET& new_socket) = 0;
        #endif
        
        virtual void sendResponse() = 0;
    protected:
        std::string ip_address_;
        int port_;
        long incoming_message_;
        unsigned int socket_address_length_;
        std::string server_message_;

        std::string buildResponse();
        
        virtual int startServer() = 0;
        virtual void closeServer() = 0;

        const int BUFFER_SIZE = 30720;
    };
}