#pragma once 
#include "http_request.hpp"
#include "http_response.hpp"
#include <unordered_map>
#include <string>
#include <functional>


namespace http
{
    class BaseController
    {
    public:
        using HandlerFunction = std::function<http::HttpResponse(const http::HttpRequest&)>; // handler functions
        virtual ~BaseController() = default;
        virtual HttpResponse handle(const HttpRequest& request) const;     
    };
} // namespace http
