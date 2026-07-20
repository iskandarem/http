#pragma once 
#include "router.hpp"


namespace http
{
    class BaseController
    {
    public:
        virtual ~BaseController() = default;
		virtual void registerHandlers(Router& router) = 0;
    };
} // namespace http
