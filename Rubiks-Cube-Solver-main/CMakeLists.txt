cmake_minimum_required(VERSION 3.20)

project(Rubiks-Cube-Solver)

set(CMAKE_CXX_STANDARD 17)

# Collect all source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Create executable
add_executable(cube ${SOURCES})

add_compile_options(-Wall -Wextra -Wpedantic)

# Output executable in build/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)