
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/test/c++)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/lib)

SET(target rbtree_test)
SET(target_interface rbtree_test.i)
SET(target_source rbtree_test.i ${CMAKE_SOURCE_DIR}/test/c++/rbtree_test.cpp)
SET(swig_output_dir ${CMAKE_CURRENT_BINARY_DIR})
SET(swig_outfile_dir ${CMAKE_CURRENT_BINARY_DIR})

include(${CMAKE_SOURCE_DIR}/cmake.include.d/using_swig.cmake)

# note the target name is prefixed with underscore
add_custom_command(TARGET _${target}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)