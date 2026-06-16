#include "http_header.hpp"
#include "utility.hpp"
#include "http_exception.hpp"
namespace http
{
    void HttpHeader::set(const std::string_view key, const std::string_view value)
    {
        auto key_to_insert = to_lower(key);
        if(headers_.contains(key_to_insert))
        {
            throw exception::BadRequest("Duplicate header");
        }
        headers_[key_to_insert] = value;
    }

    std::string_view HttpHeader::get(std::string_view key) const
    {
        std::string key_to_find = to_lower(key);
        return (headers_.contains(key_to_find))? headers_.at(key_to_find) : std::string_view{};
    }
    bool HttpHeader::contains(std::string_view key) const
    {
        return headers_.contains(std::string{key});
    }
} // namespace http
