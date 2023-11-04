cmake_minimum_required(VERSION 3.10)
project(hyprland-wallpaper-scheduler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set Debug - for debug
# Set Release - for release
set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(json)
include_directories(${CMAKE_SOURCE_DIR}/json)

find_package(PkgConfig)
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)

include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})
add_definitions(${GTKMM_CFLAGS_OTHER})

# Set COMPILE_GUI to ON or OFF based on your needs
option(COMPILE_GUI "Compile the GUI version" ON)

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

if(COMPILE_GUI)
    set(GUI
        src/gui/gui.cpp
    )
    add_definitions(-DCOMPILE_GUI)
    add_executable(hyprland-wallpaper-scheduler ${SRC} ${CORE_SRC} ${GUI})
    target_link_libraries(hyprland-wallpaper-scheduler PRIVATE ${GTKMM_LIBRARIES} )
else()
    set(TUI
        src/tui/tui.cpp
    )
    add_executable(hyprland-wallpaper-scheduler ${SRC} ${CORE_SRC} ${TUI})
endif()

target_link_libraries(hyprland-wallpaper-scheduler PRIVATE nlohmann_json::nlohmann_json)
