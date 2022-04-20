#ifndef RB_TREE_TEST_H
#define RB_TREE_TEST_H

#include <iostream>
#include <assert.h>

#include "rbtree.hpp"

void test_create_int_rbtree();
void test_create_char_rbtree();
void test_insert_root();
void test_insert_three_balanced_nodes();
void test_insert_three_unbalanced_nodes_single_rotation();
void test_insert_three_unbalanced_nodes_double_rotation();

void test_find_empty_tree();
void test_find_root();
void test_find_existing_node();
void test_find_non_existing_node();

#endif // RB_TREE_TEST_H