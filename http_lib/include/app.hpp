#pragma once 
#include "http_server.hpp"
#include "base_controller.hpp"
#include <memory>
#include <concepts>

namespace http
{
    class App
    {
    public:
        App(const std::string& ip_address = "127.0.0.1", int port = 8000);

        template<std::derived_from<BaseController> TController>
        void addController()
        {
            auto controller = std::make_unique<TController>();
            controller->registerHandlers(server_.router());
        }
        void build();
    private:
        HttpServer server_;
    };
}