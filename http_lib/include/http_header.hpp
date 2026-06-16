#pragma once 
#include <string>
#include <unordered_map>

namespace http
{
    class HttpHeader
    {
    public:
        HttpHeader() = default;
        void set(const std::string_view key, const std::string_view value);
        std::string_view get(std::string_view key) const;
        bool contains(std::string_view key) const;
    private:
        std::unordered_map<std::string, std::string> headers_;
    };
} // namespace http
