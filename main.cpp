#include <iostream>
#include "rbtree.hpp"

using namespace std;

int main() {
	RBTree<int> tree;

	auto n1 = tree.insert(20);
	auto n2 = tree.insert(10);
	auto n3 = tree.insert(30);
	auto n4 = tree.insert(25);
	auto n5 = tree.insert(40);
	auto n6 = tree.insert(50);
	auto n7 = tree.insert(60);

	tree.print_tree();

	return 0;
}
