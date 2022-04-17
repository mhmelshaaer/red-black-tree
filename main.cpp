#include <iostream>
#include "rbtree.hpp"

using namespace std;

int main() {
	RBTree<int> tree;

	auto n1 = tree.insert(10);
	cout<<n1->data<<endl;
	cout<<tree.get_root()->data<<endl;

	auto n2 = tree.insert(20);
	cout<<n2->data<<endl;
	
	tree.print_tree();

	return 0;
}
