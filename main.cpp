#include "http_lib/include/app.hpp"
#include "http_lib/include/base_controller.hpp"
#include <iostream>



class ProductController : public http::BaseController
{
public:
    void registerHandlers(http::Router& router) override
    {
        router.get("/", 
        [](const http::HttpRequest&)
        {
            http::HttpResponse response{};
            response.setStatus(http::STATUS::OK);
            response.setBody("hello from product handler");
            return response;
        }
        );
    }
};
int main()
{
    // http::HttpServer server("127.0.0.1", 8080);
    try
    {   
        auto app = http::App("127.0.0.1", 8000);
        app.addController<ProductController>();
        app.build();   
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}