INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/lib/)

SET(target rbtree_${module_lang})
SET(target_interface rbtree.i)
SET(target_source rbtree.i ${CMAKE_SOURCE_DIR}/lib/rbtree.hpp)
SET(swig_output_dir ${CMAKE_CURRENT_BINARY_DIR})
SET(swig_outfile_dir ${CMAKE_CURRENT_BINARY_DIR})

include(${CMAKE_SOURCE_DIR}/cmake.include.d/using_swig.cmake)

add_custom_command(TARGET ${target}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_BINARY_DIR}/test/${module_lang}
)
