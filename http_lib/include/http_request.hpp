#pragma once 
#include <unordered_map>
#include <string_view>
#include <string>
namespace http
{
    class HttpRequest
    {
    public:
        HttpRequest() = default;

        const std::string& getMethod() const;
        const std::string& getPath() const; // relative path without hostname
        const std::string& getUrl() const; // full path 
        const std::string& getQueryParam(std::string_view key, const std::string& _default = "" ) const;
        const std::string& getBodyAsText() const;
        std::string to_string() const;
        static HttpRequest parse(std::string_view raw_request) ;
    private:
        std::string method_;
        std::string target_; // /login/?from="linux"
        std::string path_; // /login
        std::string version_; // HTTP/1.1
        std::unordered_map<std::string, std::string> query_params_; // "from"="linux", ...
        std::string raw_body_;
    public:
        std::unordered_map<std::string, std::string> Headers;
    };
} // namespace http
