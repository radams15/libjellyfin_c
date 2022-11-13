cmake_minimum_required(VERSION 3.23)
project(jellyfin C CXX OBJC OBJCXX)

set(CMAKE_CXX_STANDARD 11)

add_library(jellyfin SHARED
        src/main/SimpleApi.cpp
        src/main/SimpleApi.h
        src/main/Conf.h
        src/main/Structures.h
        lib/cJSON/cJSON.c
        lib/cJSON/cJSON_Utils.c
        src/main/net/request.c
        src/main/net/res.c
        src/main/net/header.c

        src/main/JellyfinApi.mm
        src/main/JfItem.mm
    )

add_compile_options(-fconstant-string-class=NSConstantString)

add_executable(test src/test/main.mm)

find_package(PkgConfig REQUIRED)
pkg_check_modules(CURL REQUIRED libcurl)

include_directories(lib/ .)

include_directories(src/main)

target_link_libraries(jellyfin ${CURL_LIBRARIES} gnustep-base objc)
target_link_libraries(test jellyfin gnustep-base objc)