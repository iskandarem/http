#pragma once 
#include<functional>

namespace http
{
	class HttpRequest;
	class HttpResponse;
	using RequestHandler = std::function<http::HttpResponse(const http::HttpRequest&)>;
}
