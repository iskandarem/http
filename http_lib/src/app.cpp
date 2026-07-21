#include "app.hpp"

#ifdef _WIN32
    #include "windows_http_server.hpp"
#elif __linux__
    #include "http_server.hpp"
#endif

namespace http
{
    App::App(const std::string& ip_address, int port) : 
        server_{ip_address, port}
    {
    }

    void App::build()
    {
        server_.startListen();
    }
}
