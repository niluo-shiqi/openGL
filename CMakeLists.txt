cmake_minimum_required(VERSION 3.10)
project(hello_window VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
add_executable(hello_window 
    src/config.h 
    src/main.cpp 
    src/glad.c
)

# Add include path for GLFW
target_include_directories(hello_window PRIVATE dependencies /opt/homebrew/include)

# Manually link against the static GLFW lib
target_link_libraries(hello_window
    /opt/homebrew/lib/libglfw3.a
    "-framework OpenGL"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
    "-framework CoreFoundation"
)
