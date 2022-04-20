#include <iostream>
#include "rbtree.hpp"

using namespace std;

int main() {
	RBTree<int> tree;

	// test state00: recolor
	// auto n1 = tree.insert(20);
	// auto n2 = tree.insert(10);
	// auto n3 = tree.insert(30);
	// auto n3 = tree.insert(40);

	// test state10: single rotation
	// auto n1 = tree.insert(20);
	// auto n2 = tree.insert(10);
	// auto n3 = tree.insert(30);
	// auto n4 = tree.insert(25);
	// auto n5 = tree.insert(40);
	// auto n6 = tree.insert(50);
	// auto n7 = tree.insert(60);

	//test state11: double rotation
	auto n1 = tree.insert(8);
	auto n2 = tree.insert(18);
	auto n3 = tree.insert(5);
	auto n4 = tree.insert(15);
	auto n5 = tree.insert(17);

	tree.print_tree();

	return 0;
}
