#pragma once 
#include "status.hpp"
#include <string>
#include <string_view>
#include <unordered_map>

namespace http
{
    class HttpResponse
    {
        public:
            const std::string& getVersion() const;
            void setVersion(std::string_view version);
            STATUS getStatus() const;
            void setStatus(STATUS status);
            const std::string& getBody() const;
            void setBody(std::string_view body);
            std::string to_string() const;
			static HttpResponse notFound();
        private:
            std::string version_{"HTTP/1.1"};
            STATUS status_{STATUS::OK};
            std::string body_;
        public:
            std::unordered_map<std::string, std::string> Headers{
				{"Connection", "close"},
				{"Content-Type", "application/json"}
			};            
    };
}
