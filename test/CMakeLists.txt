cmake_minimum_required(VERSION 3.4)
project(rbtree_test)
add_executable(${PROJECT_NAME} main.cpp rbtree_test.h rbtree_test.cpp)
target_link_libraries(${PROJECT_NAME} rbtree)