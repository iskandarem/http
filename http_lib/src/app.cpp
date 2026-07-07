#include "app.hpp"

#ifdef _WIN32
    #include "windows_http_server.hpp"
#elif __linux__
    #include "linux_http_server.hpp"
#endif

namespace http
{
    App::App(const std::string& ip_address, int port)
    {
        #ifdef _WIN32
            server_ = std::make_unique<WindowsHttpServer>(ip_address, port);
        #elif __linux__
            server_ = std::make_unique<LinuxHttpServer>(ip_address, port);
        #endif
    }
    void App::addController(std::unique_ptr<BaseController> controller)
    {
        server_->setController(std::move(controller));
    }
    void App::build()
    {
        server_->startListen();
    }
}
