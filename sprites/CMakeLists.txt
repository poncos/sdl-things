cmake_minimum_required(VERSION 3.10)
project(sdl_template)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SDL3 and SDL_image using pkg-config on macOS/Homebrew
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL3 REQUIRED sdl3)
pkg_check_modules(SDL3_IMAGE REQUIRED sdl3-image)

# Source files
set(SOURCES
    main.cpp
    SDLApp.cpp
    SpriteComponent.cpp
    SpriteSheetComponent.cpp
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${SDL3_INCLUDE_DIRS} ${SDL3_IMAGE_INCLUDE_DIRS})
target_link_directories(${PROJECT_NAME} PRIVATE ${SDL3_LIBRARY_DIRS} ${SDL3_IMAGE_LIBRARY_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL3_LIBRARIES} ${SDL3_IMAGE_LIBRARIES})
