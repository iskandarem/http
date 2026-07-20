### HttpLib - a lightweight C++ HTTP-Server library 


**HttpLib** offers basic implementation for http-request, http-response, http-server and app classes. 


You can handle requests by creating a controller class that inherits from `BaseController` and overrides `registerHandlers`.

The `registerHandlers` method registers route handlers, which must have the following signature:

```cpp
HttpResponse(const HttpRequest&)
```

Controllers must also be added to the application using the `.addController<T>()` method.

`T` represents the controller type and must inherit from `BaseController`.

## Example of basic API

```cpp
#include "http_lib/include/app.hpp"
#include "http_lib/include/base_controller.hpp"

#include <exception>
#include <iostream>

class HealthController final : public http::BaseController
{
public:
    void registerHandlers(http::Router& router) override
    {
        router.get(
            "/health",
            [](const http::HttpRequest&) -> http::HttpResponse
            {
                http::HttpResponse response;

                response.setStatus(http::STATUS::OK);
                response.setBody(
                    R"({"status":"healthy"})"
                );

                return response;
            }
        );
    }
};

int main()
{
    try
    {
        http::App app{"0.0.0.0", 8000};

        app.addController<HealthController>();
        app.build();
    }
    catch (const std::exception& exception)
    {
        std::cerr << "Server error: "
                  << exception.what()
                  << '\n';

        return 1;
    }

    return 0;
}

```
