#pragma once 
#include "route.hpp"
#include <vector>

namespace http 
{
	class Router
	{
	public:
		using Handler = std::function<HttpResponse(const HttpRequest&)>;

		void get(std::string path, Handler handler);
		void post(std::string path, Handler handler);
		void put(std::string path, Handler handler);
		
		HttpResponse dispatch(const HttpRequest& request) const;
	private:
		std::vector<Route> routes_;
	};
}
