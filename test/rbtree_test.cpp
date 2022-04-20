#include "rbtree_test.h"

void test_create_int_rbtree()
{
    RBTree<int> tree;
    assert(tree.is_terminal(tree.get_root()));
}

void test_create_char_rbtree()
{
    RBTree<char> tree;
    assert(tree.is_terminal(tree.get_root()));
}

void test_insert_root()
{
    RBTree<int> tree;
    tree.insert(10);
    assert(tree.get_root()->data == 10);
}

void test_insert_three_balanced_nodes()
{
    RBTree<int> tree;
    tree.insert(20);
    tree.insert(30);
    tree.insert(10);

    assert(
        tree.get_root()->data == 20
        && tree.get_root()->left->data == 10
        && tree.get_root()->right->data == 30
    );
}

void test_insert_three_unbalanced_nodes_single_rotation()
{
    RBTree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);

    assert(
        tree.get_root()->data == 20
        && tree.get_root()->left->data == 10
        && tree.get_root()->right->data == 30
    );
}

void test_insert_three_unbalanced_nodes_double_rotation()
{
    RBTree<int> tree;
    tree.insert(20);
    tree.insert(30);
    tree.insert(25);

    assert(
        tree.get_root()->data == 25
        && tree.get_root()->left->data == 20
        && tree.get_root()->right->data == 30
    );
}


void test_find_empty_tree()
{
    RBTree<int> tree;
    assert(tree.is_terminal(tree.find(50)));
}

void test_find_root()
{
    RBTree<int> tree;
    tree.insert(20);
    assert(tree.find(20)->data == 20);
}

void test_find_existing_node()
{
    RBTree<int> tree;
    tree.insert(20);
    tree.insert(30);
    tree.insert(25);
    assert(tree.find(30)->data == 30);
}

void test_find_non_existing_node()
{
    RBTree<int> tree;
    tree.insert(20);
    tree.insert(30);
    tree.insert(25);
    assert(tree.is_terminal(tree.find(50)));
}
