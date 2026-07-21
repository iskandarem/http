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
        ~HttpServer() { closeServer(); };

        void startListen();
        void acceptConnection(int& new_socket); 
        void sendResponse(const HttpResponse& response);
        void setController(std::unique_ptr<BaseController> controller);
        Router& router();
        
    private:
       
        std::string ip_address_;
        int port_;
        long incoming_message_;
		// routers that handle requests
		Router router_;
        
        std::unique_ptr<BaseController> controller_;        
        
        static constexpr int BUFFER_SIZE = 30720;
        
        int startServer();
        void closeServer();

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
    };
}
