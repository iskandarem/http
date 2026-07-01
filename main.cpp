#include "http_lib/include/app.hpp"

int main()
{
    // http::HttpServer server("127.0.0.1", 8080);
    auto app = http::App("127.0.0.1", 8000);
    app.build();
    return 0;
}