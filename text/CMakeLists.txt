cmake_minimum_required(VERSION 3.10)
project(sdl_template)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SDL3 using pkg-config on macOS/Homebrew
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL3 REQUIRED sdl3)
pkg_check_modules(SDL3_TTF REQUIRED sdl3-ttf)

# Source files
set(SOURCES
    main.cpp
    SDLApp.cpp
    Font.cpp
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${SDL3_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL3_TTF_INCLUDE_DIRS})
target_link_directories(${PROJECT_NAME} PRIVATE ${SDL3_LIBRARY_DIRS})
target_link_directories(${PROJECT_NAME} PRIVATE ${SDL3_TTF_LIBRARY_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL3_LIBRARIES} ${SDL3_TTF_LIBRARIES})