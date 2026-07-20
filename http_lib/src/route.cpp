#include "route.hpp"

namespace http 
{
	bool Route::matches(std::string_view path, const std::unordered_map<std::string, std::string>& params) const
	{
		return path == "/";
	}
}
