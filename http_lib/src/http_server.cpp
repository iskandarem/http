#include "http_server.hpp"
#include <format>

http::HttpServer::HttpServer(const std::string &ip_address, int port):
    ip_address_(ip_address),
    port_(port),
    incoming_message_{},
    socket_address_length_{},
    socket_{},
    new_socket_{},
    server_message_(buildResponse())
    #ifdef _WIN32
    , wsaData_{}
    #endif
{
}

std::string http::HttpServer::buildResponse()
{
    // Raw string literal preserves formatting and handles quotes automatically
    const std::string html_response = R"(<!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Welcome to http_lib</title>
        <style>
            :root {
                --bg-color: #0f172a;
                --card-bg: #1e293b;
                --text-main: #f8fafc;
                --text-muted: #94a3b8;
                --accent: #38bdf8;
            }
            body {
                font-family: system-ui, -apple-system, sans-serif;
                background-color: var(--bg-color);
                color: var(--text-main);
                display: flex;
                justify-content: center;
                align-items: center;
                min-height: 100vh;
                margin: 0;
            }
            .container {
                background-color: var(--card-bg);
                padding: 2.5rem;
                border-radius: 12px;
                box-shadow: 0 10px 25px -5px rgba(0, 0, 0, 0.3);
                text-align: center;
                max-width: 450px;
                width: 90%;
                border: 1px solid #334155;
            }
            h1 {
                color: var(--accent);
                margin-top: 0;
                font-size: 2.25rem;
            }
            p {
                color: var(--text-muted);
                line-height: 1.6;
                font-size: 1.1rem;
            }
            .status-badge {
                display: inline-block;
                background-color: #065f46;
                color: #34d399;
                padding: 0.25rem 0.75rem;
                border-radius: 9999px;
                font-size: 0.875rem;
                font-weight: 600;
                margin-bottom: 1rem;
            }
        </style>
    </head>
    <body>
        <div class="container">
            <div class="status-badge">Server Online</div>
            <h1>Welcome to http_lib</h1>
            <p>Your minimalist C++ HTTP server is running successfully and serving structured HTML content over TCP sockets.</p>
        </div>
    </body>
    </html>)";

    std::string full_response = std::format(
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: {}\r\n"
        "Connection: close\r\n"
        "\r\n"
        "{}", 
        html_response.length(), 
        html_response
    );

    return full_response;
}