add_library(network STATIC)

target_sources(network
    PRIVATE
        src/socket_handler.cpp
    
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS
            include
        FILES
            include/socket_handler.hpp
            include/thread_handler.hpp
)