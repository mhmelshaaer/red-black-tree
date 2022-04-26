#include <iostream>
#include "rbtree_test.h"

int main() {

    printf("Starting tree insert tests...\n");

    test_create_int_rbtree();
    test_create_char_rbtree();
    test_insert_root();
    test_insert_three_balanced_nodes();
    test_insert_three_unbalanced_nodes_single_rotation();

    printf("Starting tree find tests...\n");

    test_find_empty_tree();
    test_find_root();
    test_find_existing_node();
    test_find_non_existing_node();

    printf("Starting tree remove tests...\n");

    test_remove_when_black_sibling_red_children_rl_rr();
    test_remove_when_black_sibling_red_children_lr_ll();
    test_remove_when_black_sibling_black_children_black_parent();
    test_remove_when_red_sibling();

    printf("All unit tests PASSED\n");
    
    return 0;
}