cmake_minimum_required(VERSION 3.23)
project(jellyfin)

set(CMAKE_CXX_STANDARD 98)

add_library(jellyfin SHARED src/main/library.cpp)
add_executable(test src/test/main.cpp)

include_directories(lib/librequest)

include_directories(src/main)

target_link_libraries(test jellyfin)
target_link_libraries(jellyfin request)
