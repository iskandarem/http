#pragma once 
#include <string>


namespace http
{
    void log(const std::string& message);
    void exitWithError(const std::string& error_message);
}