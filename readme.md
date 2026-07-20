### HttpLib - a lightweight C++ HTTP library 


**HttpLib** offers basic implementation for http-request, http-response, http-server and app classes. 


You can handle requests by creating a controller class that inherits from `BaseController` and overrides `registerHandlers`.

The `registerHandlers` method registers route handlers, which must have the following signature:

```cpp
HttpResponse(const HttpRequest&)
```

Controllers must also be added to the application using the `.addController<T>()` method.

`T` represents the controller type and must inherit from `BaseController`.

