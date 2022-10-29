cmake_minimum_required(VERSION 3.23)
project(jellyfin)

set(CMAKE_CXX_STANDARD 11)

add_library(jellyfin SHARED src/main/SimpleApi.cpp src/main/SimpleApi.h src/main/Conf.h src/main/Structures.h)
add_executable(test src/test/main.cpp)

add_subdirectory(lib/librequest)

include_directories(lib/ ${LIBREQ_HEADERS})

include_directories(src/main)

target_link_libraries(test jellyfin)
target_link_libraries(jellyfin request)
