cmake_minimum_required(VERSION 3.10.0)
project(http VERSION 0.1.0 LANGUAGES C CXX)


# Force the C++ standard globally
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Include the library subdirectory
add_subdirectory(http_lib)



# 3. Link the library to the executable
add_executable(http main.cpp)
target_link_libraries(http PRIVATE http_lib)
