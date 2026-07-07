#include "controller.hpp"

namespace
{
    std::string create_key(const std::string &method, const std::string &path)
    {
        return method + " " + path;
    }
}

namespace app
{
    http::HttpResponse HomePageController::handle(const http::HttpRequest &request) const
    {
        auto key = create_key(request.getMethod(), request.getPath());
        if(handlers_.contains(key))
        {
            auto& functor = handlers_.at(key);
            return functor(request);
        }
        return http::HttpResponse{};
    }

    http::HttpResponse HomePageController::get(const std::string &path, HandlerFunction handler)
    {
        addHandler("GET", path, std::move(handler));
    }

    void HomePageController::addHandler(const std::string &method, const std::string &path, HandlerFunction handler)
    {
        handlers_[create_key(method, path)] = std::move(handler);
    }

} // namespace app
