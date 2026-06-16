#pragma once 
#include <string>
#include <string_view>


namespace http
{
    void log(std::string_view message);
    void exitWithError(const std::string& error_message);
    std::string to_lower(std::string_view sv);
    size_t parse_content_length(std::string_view con_length);
    std::string trim(std::string_view s);
    bool is_valid_token_char(unsigned char c);
    bool is_valid_header_name(std::string_view name);
    bool contains_control_chars(std::string_view value);
}