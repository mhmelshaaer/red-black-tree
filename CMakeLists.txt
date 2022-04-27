cmake_minimum_required(VERSION 3.4)
project(rbtree)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

add_subdirectory(lib)
add_subdirectory(test)

add_subdirectory(cpp_wrappers cpp_wrappers/python)

