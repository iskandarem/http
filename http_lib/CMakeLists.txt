



if(WIN32)
    add_library(http_lib STATIC
        src/app.cpp
        src/http_server.cpp
        src/utility.cpp
        src/windows_http_server.cpp
        src/http_request.cpp) # have to add the source files here, e.g., src/tcp_server.cpp
else()
    # Create the library target (omit STATIC/SHARED to let the user decide dynamically)
    add_library(http_lib STATIC
        src/app.cpp
        src/http_server.cpp
        src/utility.cpp
        src/linux_http_server.cpp
        src/http_request.cpp
        src/http_response.cpp) # have to add the source files here, e.g., src/tcp_server.cpp
endif()

# Define public include paths so dependents can find the header files automatically
target_include_directories(http_lib PUBLIC include)

if(WIN32)
    target_link_libraries(http_lib PRIVATE ws2_32)
endif()
