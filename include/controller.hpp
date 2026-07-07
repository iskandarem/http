#pragma once 
#include <functional>
#include <unordered_map>
#include "base_controller.hpp"

namespace app
{
    class HomePageController : public http::BaseController
    {
    public:
        using HandlerFunction = std::function<http::HttpResponse(const http::HttpRequest&)>; // handler functions

        virtual ~HomePageController() = default;
        virtual http::HttpResponse handle(const http::HttpRequest& request) const override;

        http::HttpResponse get(const std::string& path, HandlerFunction handler);

    private:
        std::unordered_map<std::string, HandlerFunction> handlers_;
        
        void addHandler(const std::string& method, const std::string& path, HandlerFunction handler);
    };
} // namespace app
