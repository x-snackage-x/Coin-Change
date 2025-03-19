cmake_minimum_required(VERSION 3.10.0)
project(coin-change VERSION 0.1.0 LANGUAGES C)

# Set the output directory for executables to the root directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

# Generate a Makefile
if (WIN32)
    set(CMAKE_GENERATOR "NMake Makefiles")
else()
    set(CMAKE_GENERATOR "Unix Makefiles")
endif()

add_executable(coin-change coin-change-cli.c coin-change.c)
add_executable(coin-change-test coin-change-test.c coin-change.c)

