#include "http_response.hpp"
#include <format>
#include <functional>

namespace http
{
    const std::string &HttpResponse::getVersion() const
    {
        return version_;
    }

    void HttpResponse::setVersion(std::string_view version)
    {
        version_ = version;
    }

    STATUS HttpResponse::getStatus() const
    {
        return status_;
    }

    void HttpResponse::setStatus(STATUS status)
    {
        status_ = status;
    }

    const std::string &HttpResponse::getBody() const
    {
        return body_;
    }

    void HttpResponse::setBody(std::string_view body)
    {
        body_ = body;
    }

    std::string HttpResponse::to_string() const
    {
        auto statusInfo = getStatusInfo(status_);
        return std::format(
            "{} {} {}" // Version, status code, status 
            "{}" // Headers
            "\r\n"
            "{}", // Body
            version_,
            statusInfo.code,
            statusInfo.name,
            [this]()
            {
                std::string headers{};
                for(const auto& [key, val] : Headers)
                {
                    headers += key + ": " + val + "\r\n";
                }
                return headers;
            }(),
            body_
        );
    }
	HttpResponse HttpResponse::notFound()
	{
		HttpResponse response{};
		response.setStatus(NOT_FOUND);
		response.setBody("Not Found");
		return response;
	}
} // namespace http
