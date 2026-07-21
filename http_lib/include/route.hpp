#pragma once
#include "http_request.hpp"
#include "http_response.hpp"
#include "request_handler.hpp" 
#include <string>


namespace http
{
    struct Route 
    {
        std::string method_;
        std::string pathPattern_;
		RequestHandler handler_;
		bool matches(const HttpRequest& request) const;
    };
} // namespace http
