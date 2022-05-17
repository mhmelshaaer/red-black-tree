cmake_minimum_required(VERSION 3.16)
project(rbtree)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

# Build the rbtree lib
add_subdirectory(lib)

option(python "Build python" OFF)
option(csharp "Build csharp" OFF)
option(build_cpp_test "Build cpp" OFF)

if(python)

  set(module_lang "python")
  add_subdirectory(wrappers ${CMAKE_BINARY_DIR}/wrappers/python)

elseif(csharp)

  set(module_lang "csharp")
  add_subdirectory(wrappers ${CMAKE_BINARY_DIR}/wrappers/csharp)

endif()

add_subdirectory(test)

