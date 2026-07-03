#include "http_request.hpp"
#include "exception/bad_request.hpp"
#include "utility.hpp"
#include <algorithm>
#include <ranges>
#include <vector>
#include <sstream>

namespace http
{
    const std::string& HttpRequest::getMethod() const
    {
        return method_;
    }

    const std::string& HttpRequest::getPath() const
    {
        return path_;
    }

    const std::string& HttpRequest::getUrl() const
    {
        return target_;
    }

    const std::string& HttpRequest::getQueryParam(std::string_view key, const std::string& _default) const
    {
        return (query_params_.contains(std::string{key}))? query_params_.at(std::string{key}) : _default;
    }
    
    const std::string& HttpRequest::getBodyAsText() const
    {
        return raw_body_;
    }

    std::string HttpRequest::to_string() const
    {
        std::string result{};
        
        //----------------
        // Request line
        //----------------
        result += 
            method_ + " " +
            target_ + " " +
            version_ + "\r\n"; // request line

        //-----------------
        // Headers
        //-----------------
        for(const auto& [key, val] : Headers)
        {
            result += key + ":" + " " + val + "\r\n";
        } 

        //----------------
        // Body
        //----------------
        result += "\r\n";
        result += raw_body_; // combine body

        return result;
    }

    HttpRequest HttpRequest::parse(std::string_view raw_request)
    {
        const size_t header_end = raw_request.find("\r\n\r\n");
        if(header_end == std::string_view::npos)
        {
            throw http::exception::BadRequest("Incomplete or malformed HTTP request");
        }
        
        std::string_view header_part = raw_request.substr(0, header_end);
        std::string_view body_part = raw_request.substr(header_end+4);

        HttpRequest req;

        //--------------------------
        // Parse request line
        //--------------------------
        const size_t first_line_end = header_part.find("\r\n");
        
        std::string_view request_line = 
        (first_line_end == std::string_view::npos)
        ? header_part
        : header_part.substr(0, first_line_end);

        const size_t method_end = request_line.find(' ');
        if(method_end == std::string_view::npos)
        {
            throw http::exception::BadRequest("Invalid request line");
        }
        
        const size_t path_start = method_end+1;
        const size_t path_end = request_line.find(' ', path_start);

        if(path_end == std::string_view::npos)
        {
            throw exception::BadRequest("Invalid request line");
        }
        const size_t version_start = path_end+1;
        
        req.method_ = request_line.substr(0, method_end); //method parsed
        req.path_ = request_line.substr(path_start, path_end-path_start);
        req.version_ = request_line.substr(version_start);

        if(req.method_.empty() || req.path_.empty() || req.version_.empty())
        {
            throw exception::BadRequest("Invalid request line");
        }

        if(req.version_ != "HTTP/1.1" && req.version_ != "HTTP/1.0")
        {
            throw exception::BadRequest("Unsupported HTTP version");
        }

        if(req.path_[0] != '/')
        {
            throw exception::BadRequest("Invalid path");
        }


        for(unsigned char c : req.method_)
        {
            if(!is_valid_token_char(c))
            {
                throw exception::BadRequest("Invalid method");
            }
        }

        //-------------------
        // Parse headers
        //-------------------

        size_t pos = 
        (first_line_end == std::string_view::npos)
        ? header_part.size()
        : first_line_end+2;

        while(pos<header_part.size())
        {
            size_t line_end = header_part.find("\r\n", pos);
            
            if(line_end == std::string_view::npos)
            {
                line_end = header_part.size();
            }
            
            std::string_view line = header_part.substr(pos, line_end-pos);
            
            if(line.empty())
            {
                break;
            } 

            const size_t colon = line.find(':');

            if(colon == std::string_view::npos)
            {
                throw exception::BadRequest("Malformed header");
            }
            
            std::string_view key = line.substr(0, colon);
            std::string val = trim(line.substr(colon+1));

            if(!is_valid_header_name(key))
            {
                throw exception::BadRequest("Invalid header name");
            }

            if(contains_control_chars(val))
            {
                throw exception::BadRequest("Invalid header value");
            }
            std::string lower_key = http::to_lower(key);
            if(req.Headers.contains(lower_key))
            {
                throw exception::BadRequest("Double header name");
            }
            req.Headers.insert(std::pair<std::string, std::string>(lower_key, val));
            
            pos = line_end+2;
        }

        //-----------------------
        // Parse body using Content-Length
        //-----------------------

        if(req.Headers.contains("content-length"))
        {
            std::size_t content_length = std::stoi(std::string{req.Headers.at("content-length")});
            if(body_part.size() < content_length)
            {
                throw exception::BadRequest("Incomplete body");
            }
            
            req.raw_body_ = std::string{body_part.substr(0, content_length)};
        }
        else
        {
            req.raw_body_.clear();
        }
        return req;
    }
} // namespace http
