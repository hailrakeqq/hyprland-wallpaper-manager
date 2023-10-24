cmake_minimum_required(VERSION 3.10)
project(hyprland-wallpaper-scheduler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Set Debug - for debug
#Set Release - for release
set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(json)
include_directories(${CMAKE_SOURCE_DIR}/json)
set(SRC
    src/main.cpp
    src/cmdUI.cpp
    src/configurator.cpp
    src/utils.cpp
)
set(CORE_SRC
    src/core/imageManager.cpp
    src/core/settings.cpp
    src/core/wallpaperChanger.cpp
    src/core/scheduler.cpp
)

add_executable(hyprland-wallpaper-scheduler ${SRC} ${CORE_SRC})
target_link_libraries(hyprland-wallpaper-scheduler PRIVATE nlohmann_json::nlohmann_json)