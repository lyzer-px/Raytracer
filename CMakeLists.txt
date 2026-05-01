cmake_minimum_required(VERSION 3.28)

project(raytracer VERSION 1.0
        LANGUAGES CXX)

find_program(CPP_COMPILER NAMES clang++ REQUIRED FALSE)
if(CPP_COMPILER)
   set(CMAKE_C_COMPILER ${CPP_COMPILER} CACHE FILEPATH "clang++ compiler" FORCE)
   message(STATUS "Using clang++: ${CPP_COMPILER}")
else()
   message(STATUS "clang++ not found, using default CXX compiler")
endif()

find_program(C_COMPILER NAMES clang REQUIRED FALSE)
if(C_COMPILER)
   set(CMAKE_C_COMPILER ${C_COMPILER} CACHE FILEPATH "Epitech C compiler" FORCE)
   message(STATUS "Using Epitech C compiler: ${C_COMPILER}")
else()
   message(STATUS "clang++ not found, using default CXX compiler")
endif()

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(warning_options INTERFACE)

target_compile_options(warning_options INTERFACE -Wall #[[-Wextra -Werror]])

add_subdirectory(src)

enable_testing()

add_subdirectory(tests)
