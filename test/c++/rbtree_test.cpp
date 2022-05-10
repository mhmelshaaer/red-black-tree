#include "rbtree_test.h"

void run() {

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
    
    test_remove_when_internal_node();
    test_remove_when_black_sibling_red_children_rl_rr();
    test_remove_when_black_sibling_red_children_lr_ll();
    test_remove_when_black_sibling_black_children_black_parent();
    test_remove_when_red_sibling();

    printf("All unit tests PASSED\n");
}

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

void test_remove_when_internal_node()
{
    RBTree<int> tree;
    std::vector<int> to_be_inserted { 3, 5, 7 };
    for(const auto& v: to_be_inserted)
    {
        tree.insert(v);
    }

	tree.remove(5);

    assert(tree.get_root()->data == 7);
}

void test_remove_when_black_sibling_red_children_rl_rr()
{
    RBTree<int> tree;
    std::vector<int> to_be_inserted { 8, 18, 5, 15, 17, 6 };
    for(const auto& v: to_be_inserted)
    {
        tree.insert(v);
    }

	tree.remove(5);
	tree.remove(18);
	tree.remove(6);
    
    assert(
        tree.get_root()->data == 15 && tree.is_black(tree.get_root()) 
        && tree.get_root()->left->data == 8 && tree.is_black(tree.get_root()->left) 
        && tree.get_root()->right->data == 17 && tree.is_black(tree.get_root()->right) 
    );
}

void test_remove_when_black_sibling_red_children_lr_ll()
{
    RBTree<int> tree;
    std::vector<int> to_be_inserted { 20, 15, 25, 10, 18, 30 };
    for(const auto& v: to_be_inserted)
    {
        tree.insert(v);
    }

	tree.remove(25);
	tree.remove(10);
	tree.remove(30);

    assert(
        tree.get_root()->data == 18 && tree.is_black(tree.get_root()) 
        && tree.get_root()->left->data == 15 && tree.is_black(tree.get_root()->left) 
        && tree.get_root()->right->data == 20 && tree.is_black(tree.get_root()->right) 
    );
}

void test_remove_when_black_sibling_black_children_black_parent()
{
    RBTree<int> tree;
    std::vector<int> to_be_inserted { 15, 10, 20, 5, 13, 18, 25, 2, 8, 1, 3, 4 };
    for(const auto& v: to_be_inserted)
    {
        tree.insert(v);
    }

	tree.remove(4);
	tree.remove(2);
	tree.remove(3);
	tree.remove(8);

    assert(
        tree.get_root()->data == 10 && tree.is_black(tree.get_root()) 
        && tree.get_root()->right->data == 15
        && tree.is_red(tree.get_root()->right) 
        && tree.get_root()->left->left->data == 1
        && tree.is_red(tree.get_root()->left->left)
    );
}

void test_remove_when_red_sibling()
{
    RBTree<int> tree;
    std::vector<int> to_be_inserted { 15, 10, 20, 5, 13, 18, 25, 2, 8, 1, 3, 4 };
    for(const auto& v: to_be_inserted)
    {
        tree.insert(v);
    }

	tree.remove(8);

    assert(
        tree.get_root()->data == 10 && tree.is_black(tree.get_root()) 
        && tree.get_root()->left->data == 2
        && tree.is_black(tree.get_root()->left)
        && tree.get_root()->left->right->data == 4
        && tree.is_red(tree.get_root()->left->right)
    );
}

