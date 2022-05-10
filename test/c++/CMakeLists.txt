set(target main)
add_executable(${target} main.cpp rbtree_test.h rbtree_test.cpp)
target_link_libraries(${target} rbtree)