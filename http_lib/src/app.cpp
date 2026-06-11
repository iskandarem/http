#include "app.hpp"

#ifdef _WIN32
    #include "windows_tcp_server.hpp"
#elif __linux__
    #include "linux_tcp_server.hpp"
#endif

namespace http
{
    App::App(const std::string& ip_address, int port)
    {
        #ifdef _WIN32
            server_ = std::make_unique<WindowsTcpServer>(ip_address, port);
        #elif __linux__
            server_ = std::make_unique<LinuxTcpServer>(ip_address, port);
        #endif
    }
    void App::build()
    {
        server_->startListen();
    }
}
