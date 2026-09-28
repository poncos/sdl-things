cmake_minimum_required(VERSION 3.10)
project(sdl_template)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find required libraries
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL3 REQUIRED sdl3)
pkg_check_modules(TMXLITE REQUIRED tmxlite)
pkg_check_modules(SDL3_IMAGE REQUIRED sdl3-image)

# Source files
set(SOURCES
    main.cpp
    SDLApp.cpp
    TmxTileMap.cpp
    MathDefinitions.cpp
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${SDL3_INCLUDE_DIRS} ${TMXLITE_INCLUDE_DIRS} ${SDL3_IMAGE_INCLUDE_DIRS})
target_link_directories(${PROJECT_NAME} PRIVATE ${SDL3_LIBRARY_DIRS} ${TMXLITE_LIBRARY_DIRS} ${SDL3_IMAGE_LIBRARY_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL3_LIBRARIES} ${TMXLITE_LIBRARIES} ${SDL3_IMAGE_LIBRARIES})
