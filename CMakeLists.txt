cmake_minimum_required(VERSION 3.4)
project(main)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(lib)
add_subdirectory(test)

target_link_libraries(${PROJECT_NAME} rbtree)
