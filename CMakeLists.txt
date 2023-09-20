cmake_minimum_required(VERSION 3.16)

project(nc)

set(CMAKE_CXX_STANDARD 20)

add_executable(nc
        main.cpp
        client.cpp
        server.cpp
        common.cpp
        common.hpp)
