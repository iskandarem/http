#pragma once 
#include <stdexcept>

namespace http::exception
{
    
    class BadRequest : public std::runtime_error
    {
        public: 
            using std::runtime_error::runtime_error;
    };
} // namespace http::exception
