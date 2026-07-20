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
		bool matches(std::string_view path, const std::unordered_map<std::string, std::string>& params) const;
    };
} // namespace http
