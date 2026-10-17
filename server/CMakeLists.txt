add_executable(server)

target_sources(server
    PRIVATE
        src/main.cpp
        src/server.cpp
        src/client.cpp
        src/auth_handler.cpp
        src/chat_handler.cpp
        src/shop_handler.cpp
)

target_link_libraries(server
    PRIVATE
        network
)

set_target_properties(server
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)