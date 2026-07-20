#include "route.hpp"

namespace http 
{
	bool Route::matches(const HttpRequest& request) const
	{
		if(request.getMethod() != method_) return false;
		if(request.getPath() != pathPattern_) return false;
		return true;	
	}
}
