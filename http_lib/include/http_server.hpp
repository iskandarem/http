#pragma once
#include "base_controller.hpp"
#include "router.hpp"
#include <string>
#include <memory>
#ifdef _WIN32
    #include<winsock2.h>
    #include <WS2tcpip.h>
#elif __linux__
    #include <arpa/inet.h>
#endif

namespace http
{
    class HttpServer
    {
    public:
        HttpServer(const std::string& ip_address = "127.0.0.1", int port = 8000);
        virtual ~HttpServer() = default;

        virtual void startListen() = 0;

        #ifdef __linux__
            virtual void acceptConnection(int& new_socket) = 0;
        #elif _WIN32
            virtual void acceptConnection(SOCKET& new_socket) = 0;
        #endif
        
        void setController(std::unique_ptr<BaseController> controller);
        Router& router();
        virtual void sendResponse(const HttpResponse& response) = 0;
    protected:
        std::string ip_address_;
        int port_;
        long incoming_message_;
        #ifdef __linux__ 

        unsigned int socket_address_length_;
        int socket_;
        int new_socket_;
        struct sockaddr_in socket_address_;

        #elif _WIN32

        int socket_address_length_;
        SOCKET socket_;
        SOCKET new_socket_;
        struct sockaddr_in socket_address_;
        WSADATA wsaData_;

        #endif
		// routers that handle requests
		Router router_;
        virtual int startServer() = 0;
        virtual void closeServer() = 0;

        std::unique_ptr<BaseController> controller_;        

        static constexpr int BUFFER_SIZE = 30720;
    };
}
