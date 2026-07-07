#pragma once 
#include "http_server.hpp"
#include <memory>


namespace http
{
    class App
    {
    public:
        App(const std::string& ip_address = "127.0.0.1", int port = 8000);
        void addController(std::unique_ptr<BaseController> controller); 
        void build();
    private:
        std::unique_ptr<HttpServer> server_;
    };
}