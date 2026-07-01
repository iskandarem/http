#pragma once 
#include <stdexcept>

namespace http::exception
{
    class HttpServerException : public std::runtime_error
    {
    public:
        using std::runtime_error::runtime_error;
    };
}