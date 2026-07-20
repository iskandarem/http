#include "http_server.hpp"
#include <format>

http::HttpServer::HttpServer(const std::string &ip_address, int port):
    ip_address_(ip_address),
    port_(port),
    incoming_message_{},
    socket_address_length_{},
    socket_{},
    new_socket_{}
    #ifdef _WIN32
    , wsaData_{}
    #endif
{
}

void http::HttpServer::setController(std::unique_ptr<BaseController> controller)
{
    controller_ = std::move(controller);
}

http::Router& http::HttpServer::router()
{
    return router_;
}