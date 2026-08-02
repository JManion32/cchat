cmake_minimum_required(VERSION 3.28)

project(CChat)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# The server and the web client need no Qt. Turning this off lets someone work
# on those without installing it.
option(BUILD_CLIENT_GUI "Build the Qt desktop client" ON)

add_subdirectory(shared)
add_subdirectory(server)

if(BUILD_CLIENT_GUI)
    add_subdirectory(client_gui)
endif()