cmake_minimum_required(VERSION 3.10)
project(kde-wallpaper-scheduler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

add_executable(kde-wallpaper-scheduler ${SRC} ${CORE_SRC})
target_link_libraries(kde-wallpaper-scheduler PRIVATE nlohmann_json::nlohmann_json)