#pragma once 
#include "route.hpp"
#include <vector>

namespace http 
{
	class Router
	{
	public:
		void get(std::string path, RequestHandler handler);
		void post(std::string path, RequestHandler handler);
		void put(std::string path, RequestHandler handler);
		
		HttpResponse dispatch(const HttpRequest& request) const;
	private:
		std::vector<Route> routes_;
	};
}
