#pragma once
#include "http_request.hpp"
#include "http_response.hpp" 
#include <string>
#include <functional>


namespace http
{
    struct Route 
    {
        std::string method_;
        std::string pathPattern_;
        std::function<HttpResponse(const HttpRequest&)> handler_;
		bool matches(const HttpRequest& request) const;
    };
} // namespace http
