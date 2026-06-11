#pragma once 
#include "tcp_server.hpp"
#include <memory>


namespace http
{
    class App
    {
    public:
        App(const std::string& ip_address = "127.0.0.1", int port = 8000);
    
    private:
        std::unique_ptr<TcpServer> server_;
    };
}