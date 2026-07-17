#include "http_lib/include/app.hpp"
#include "http_lib/include/base_controller.hpp"

#include <iostream>
int main()
{
    // http::HttpServer server("127.0.0.1", 8080);
    try
    {   
        auto app = http::App("127.0.0.1", 8000);
        app.build();   
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}