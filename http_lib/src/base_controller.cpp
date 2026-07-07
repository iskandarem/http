#include "base_controller.hpp"

namespace http
{
    HttpResponse BaseController::handle(const HttpRequest &request) const
    {
        return HttpResponse{};
    }

} // namespace http
