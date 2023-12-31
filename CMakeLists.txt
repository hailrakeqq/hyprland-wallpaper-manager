cmake_minimum_required(VERSION 3.10)
project(hyprland-wallpaper-manager)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(json)
include_directories(${CMAKE_SOURCE_DIR}/json)

find_package(PkgConfig)
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)

include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})
add_definitions(${GTKMM_CFLAGS_OTHER})

# Set COMPILE_GUI to ON or OFF based on your needs
option(COMPILE_GUI "Compile the GUI version" ON)
option(DEBUG "Debug version?" OFF)

set(SRC
    src/main.cpp
    src/utils.cpp
)

set(CORE_SRC
    src/core/wallpaperManager.cpp
    src/core/wallpaperChanger.cpp
    src/core/scheduler.cpp
    src/core/configurator.cpp
)

if(DEBUG)
    # Set Debug - for debug
    # Set Release - for release
    set(CMAKE_BUILD_TYPE Debug)
    add_compile_definitions(DEBUG)
else()
    set(CMAKE_BUILD_TYPE Release)
endif()

if(COMPILE_GUI)
    set(UI_FILES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ui)

    set(GUI
        src/gui/gui.cpp
        src/gui/settings_ui.cpp
    )
    add_definitions(-DCOMPILE_GUI)
    file(COPY ${UI_FILES_DIR} DESTINATION ${CMAKE_BINARY_DIR}/)
    add_executable(hyprland-wallpaper-manager ${SRC} ${CORE_SRC} ${GUI})
    target_link_libraries(hyprland-wallpaper-manager PRIVATE ${GTKMM_LIBRARIES} )
else()
    set(TUI
        src/tui/tui.cpp
    )
    add_executable(hyprland-wallpaper-manager ${SRC} ${CORE_SRC} ${TUI})
endif()

target_link_libraries(hyprland-wallpaper-manager PRIVATE nlohmann_json::nlohmann_json)
