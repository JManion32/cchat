cmake_minimum_required(VERSION 3.28)

project(cchat_server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(server
    src/main.cpp
    src/server.cpp
    src/client.cpp
    src/auth_handler.cpp
    src/chat_handler.cpp
    src/shop_handler.cpp
)

target_include_directories(
    server PUBLIC
    include ../shared/include
)

target_link_libraries(server
    shared
)

set_target_properties(
    server PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)