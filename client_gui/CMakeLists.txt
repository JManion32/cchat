cmake_minimum_required(VERSION 3.28)

project(cchat_client)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Gui
    Widgets
    Network
)

add_executable(client
    src/main.cpp
    src/client.cpp
    src/themes.cpp
)

target_include_directories(client
    PUBLIC
    include
    ../shared/include
)

target_link_libraries(client
    shared
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Network
    pthread
)

set_target_properties(client
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)