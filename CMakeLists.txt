cmake_minimum_required(VERSION 3.16)
project(rbtree)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

# Build the rbtree lib
add_subdirectory(lib)

option(PYTHON_SDK "Build python SDK" OFF)
option(CSHARP_SDK "Build csharp SDK" OFF)

if(PYTHON_SDK)

  set(module_lang "python")
  add_subdirectory(wrappers ${CMAKE_BINARY_DIR}/wrappers/python)

endif()

if(CSHARP_SDK)

  set(module_lang "csharp")
  add_subdirectory(wrappers ${CMAKE_BINARY_DIR}/wrappers/csharp)

endif()

add_subdirectory(test)

