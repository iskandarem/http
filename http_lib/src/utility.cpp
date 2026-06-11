#include "utility.hpp"
#include <iostream>

namespace http
{

    void log(const std::string& message)
    {
        std::cout << message << std::endl;
    }

    void exitWithError(const std::string& error_message)
    {
        std::cerr << "Error: " << error_message << std::endl;
        exit(EXIT_FAILURE);
    }
}