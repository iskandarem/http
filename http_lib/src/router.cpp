#include "router.hpp"

namespace http 
{
	
	void Router::get(std::string path, RequestHandler handler)
	{
		routes_.push_back(
			Route{
				"GET",
				path,
				handler
			}
		);
	}

	
	void Router::post(std::string path, RequestHandler handler)
	{
		routes_.push_back(
			Route{
				"POST",
				path, 
				handler
			}
		);
	}

	void Router::put(std::string path, RequestHandler handler)
	{
		routes_.push_back(
			Route{
				"PUT",
				path,
				handler
			}
		);
	}
	
	HttpResponse Router::dispatch(const HttpRequest& request) const
	{
		auto router = std::find_if(routes_.begin(), routes_.end(), [&request](const auto& route){
			return route.matches(request);
		});
		if(router != routes_.end()) return router->handler_(request);
		return HttpResponse::notFound();
	}
}

	
