#include <iostream>
#include "rbtree.hpp"

using namespace std;

int main() {
	RBTree<int> tree;

	auto n1 = tree.insert(20);
	auto n2 = tree.insert(10);
	auto n3 = tree.insert(30);
	auto n4 = tree.insert(40);

	tree.print_tree();

	return 0;
}
