#include "tcp_server.hpp"

http::TcpServer::TcpServer(const std::string &ip_address, int port):
    ip_address_(ip_address),
    port_(port),
    incoming_message_{},
    socket_address_length_{},
    server_message_(buildResponse())
{
}

std::string http::TcpServer::buildResponse()
{
    std::string response = "HTTP/1.1 200 OK\r\n";
    response += "Content-Type: text/plain\r\n";
    response += "Content-Length: 13\r\n";
    response += "\r\n";
    response += "Hello, World!";
    return response;
}