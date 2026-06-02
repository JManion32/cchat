add_library(shared STATIC
    src/socket_handler.cpp
)

target_include_directories(shared
    PUBLIC
    include
)