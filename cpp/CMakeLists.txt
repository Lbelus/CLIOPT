cmake_minimum_required(VERSION 3.22)
project(CppCliOpt VERSION 0.0.1 LANGUAGES CXX C ASM_NASM)

# GENERATE THE LIB OBJECT

# Set C standard
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find NASM
enable_language(ASM_NASM)
if(NOT CMAKE_ASM_NASM_COMPILER_LOADED)
    message(FATAL_ERROR "NASM compiler not found")
endif()

# Add include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add NASM source files
file(GLOB_RECURSE ASM_SOURCES "src/*.asm")

# Add source files excluding main.c
file(GLOB_RECURSE SOURCES "src/*.c")
list(FILTER SOURCES EXCLUDE REGEX ".*main\\.c$")

# Add source files excluding main.cpp
file(GLOB_RECURSE CPP_SOURCES "src/*.cpp")
list(FILTER CPP_SOURCES EXCLUDE REGEX ".*main\\.cpp$")

# Option to enable or disable CFLAGS
option(ENABLE_CFLAGS "Enable CFLAGS" OFF)

# Create an object library from the source files
add_library(CppCliOptObj OBJECT ${ASM_SOURCES} ${CPP_SOURCES} ${SOURCES})


if(ENABLE_CFLAGS)
    target_compile_options(CppCliOptObj PRIVATE 
    $<$<COMPILE_LANGUAGE:C>:-fsanitize=address -Wall -Wextra -Werror>
    $<$<COMPILE_LANGUAGE:CXX>:-fsanitize=address -Wall -Wextra -Werror>
    )
    # Link with sanitizer library for C and C++ targets
    target_link_libraries(CppCliOptObj PRIVATE -fsanitize=address)
endif()




# Create the main executable with main.cpp
add_executable(CppCliOpt src/main.cpp)
target_link_libraries(CppCliOpt PRIVATE CppCliOptObj)