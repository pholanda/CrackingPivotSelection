cmake_minimum_required(VERSION 3.9)
project(CrackingPivotSelection)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE off)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_MACOSX_RPATH 1)

set(CMAKE_CXX_FLAGS_DEFAULT "-O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -g -O3")

set(CMAKE_C_FLAGS_DEFAULT "${CMAKE_CXX_FLAGS_DEFAULT}")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")

if (NOT CMAKE_BUILD_TYPE)
    message(FATAL_ERROR "Choose the type of build by setting -DCMAKE_BUILD_TYPE=<type>, options are: Debug Release RelWithDebInfo MinSizeRel.")
endif()

if (NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

add_executable(generate_column
        src/data/file_manager.cpp src/data/generate_column.cpp)

add_executable(generate_query
        src/data/file_manager.cpp src/data/generate_query.cpp)

add_executable(main
        src/data/file_manager.cpp src/cracking/avl_tree.cpp src/util.cpp src/cracking/standard_cracking.cpp src/main.cpp)