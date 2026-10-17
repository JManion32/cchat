cmake_minimum_required(VERSION 3.28.3)

project(CChat)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_CLIENT_GUI "Build the Qt desktop client" ON)

add_subdirectory(network)
add_subdirectory(server)

if(BUILD_CLIENT_GUI)
    add_subdirectory(client_gui)
endif()