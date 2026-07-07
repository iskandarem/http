#ifdef __linux__
#pragma once 
#include "http_server.hpp"
namespace http
{
    class LinuxHttpServer : public HttpServer
    {
    public:
        LinuxHttpServer(const std::string& ip_address = "127.0.0.1", int port = 8000);
        virtual ~LinuxHttpServer() override { closeServer(); };

        virtual void startListen() override;
        virtual void acceptConnection(int& new_socket) override; 
        virtual void sendResponse(const HttpResponse& response) override;

        virtual int startServer() override;
        virtual void closeServer() override;
    };
}
#endif