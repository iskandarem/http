#pragma once 
#include "http_header.hpp"

namespace http
{
    class HttpRequest
    {
    public:
        HttpRequest() = default;    
        std::string_view getMethod() const;
        std::string_view getPath() const; // relative path without hostname
        std::string_view getUrl() const; // full path 
        std::string_view getQueryParam(std::string_view key, std::string_view _default = "" ) const;
        std::string_view getBodyAsText() const;

        static HttpRequest parse(std::string_view raw_request) ;
    private:
        std::string method_;
        std::string target_; // /login/?from="linux"
        std::string path_; // /login
        std::string version_; // HTTP/1.1
        std::unordered_map<std::string, std::string> query_params_; // "from"="linux", ...
        std::string raw_body_;
    public:
        HttpHeader headers_; 
    };
} // namespace http
