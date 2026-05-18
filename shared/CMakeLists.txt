add_library(shared
    src/socket_handler.cpp
)

target_include_directories(shared
    PUBLIC
    include
)