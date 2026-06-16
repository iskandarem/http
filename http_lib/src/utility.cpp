#include "utility.hpp"
#include "http_exception.hpp"
#include <iostream>
#include <algorithm>
#include <ranges>
#include <charconv>
#include <format>
namespace http
{

    void log(std::string_view message)
    {
        std::cout << message << std::endl;
    }

    void exitWithError(const std::string& error_message)
    {
        std::cerr << "Error: " << error_message << std::endl;
        throw exception::HttpServerError(std::format("Error: {}", error_message));
    }
    std::string to_lower(std::string_view sv)
    {
        std::string str(sv.size(), '\0');
        std::ranges::transform(sv,str.begin(), [](char c)
        {
            return std::tolower(c);
        });
        return str;
    }
    size_t parse_content_length(std::string_view con_length)
    {
        size_t length = 0;
        auto begin = con_length.data();
        auto end = con_length.data() + con_length.size();
        auto [ptr, ec] = std::from_chars(begin, end, length);
        if(ec != std::errc{} || ptr != end)
        {
            throw exception::BadRequest("Invalid Content-Length");
        } 
        return length;
    }
    std::string trim(std::string_view s)
    {
        while(!s.empty() && (s.front() == ' ' || s.front() == '\t'))
        {
            s.remove_prefix(1);
        }
        while(!s.empty() && (s.back() == ' ' || s.back() == '\t'))
        {
            s.remove_suffix(1);
        }
        return std::string{s};
    }
    bool is_valid_token_char(unsigned char c)
    {
        static constexpr std::string_view separators = "()<>@,;:\\\"/[]?={} \t";
        return c > 31 && c < 127 && separators.find(static_cast<char>(c))==std::string_view::npos;
    }
    bool is_valid_header_name(std::string_view name)
    {
        if(name.empty()) 
        {
            return false;
        }
        for(unsigned char c : name)
        {
            if(!is_valid_token_char(c))
            {
                return false;
            }
        }
        return true;
    }
    bool contains_control_chars(std::string_view value)
    {
        for(unsigned char c : value)
        {
            if(c<32 && c!='\t')
            {
                return true;
            }
            if(c==127)
            {
                return true;
            }
        }
        return false;
    }
}