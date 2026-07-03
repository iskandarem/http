#pragma once 
#include <string>

namespace http
{
    enum STATUS
    {
        OK = 200,
        CREATED = 201,
        NOT_FOUND = 404
    };
    struct StatusInfo
    {
        int code{200};
        std::string_view name;
    };
    constexpr StatusInfo getStatusInfo(STATUS s)
    {
        switch (s)
        {
        case OK: return {200, "OK"};
        case CREATED: return {200, "CREATED"};
        case NOT_FOUND: return {404, "NOT_FOUND"};
        
        default: return {200, "OK"};
        }
    }
} // namespace http