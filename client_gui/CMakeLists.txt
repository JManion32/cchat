cmake_minimum_required(VERSION 3.28)

project(cchat_client)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Deliberately not REQUIRED: CMake's own not-found message for Qt is a wall of
# text about Qt6Config.cmake that does not say how to fix it.
find_package(Qt6 QUIET COMPONENTS
    Core
    Gui
    Widgets
    Network
)

if(NOT Qt6_FOUND)
    message(FATAL_ERROR
        "Qt6 was not found, so the desktop client cannot be built.\n"
        "\n"
        "Install it from your package manager:\n"
        "    sudo apt install qt6-base-dev\n"
        "\n"
        "Or, if you use the Qt online installer, point CMake at that copy:\n"
        "    cmake --preset dev -D CMAKE_PREFIX_PATH=$ENV{HOME}/Qt/<version>/gcc_64\n"
        "\n"
        "Or build just the server and skip Qt entirely:\n"
        "    cmake --preset dev -D BUILD_CLIENT_GUI=OFF\n"
        "\n"
        "See the README for how to make this permanent.")
endif()

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