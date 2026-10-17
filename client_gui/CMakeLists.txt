set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6
    QUIET
    COMPONENTS
        Core
        Gui
        Widgets
        Network
)

if(NOT Qt6_FOUND)
    message(FATAL_ERROR
        "Qt6 was not found, so the desktop client cannot be built."
    )
endif()

add_executable(client_gui)

target_sources(client_gui
    PRIVATE
        src/main.cpp
        src/client.cpp
        src/themes.cpp
)

target_link_libraries(client_gui
    PRIVATE
        network
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Network
        pthread
)

set_target_properties(client_gui
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)