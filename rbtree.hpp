#ifndef RB_TREE
#define RB_TREE

#include <iostream>
#include <memory>


template<typename V>
struct RBTreeNode
{
    V data;
    std::shared_ptr<RBTreeNode> left;
    std::shared_ptr<RBTreeNode> right;
    // no resource management needed since a node cannot exist without a parent.
    RBTreeNode* parent;
    int color = 0;
};

template<typename T>
class RBTree {
private:
    typedef std::shared_ptr<RBTreeNode<T>> NodePtr;
	NodePtr _root;
	NodePtr _TNULL;

public:
	RBTree() {
		_TNULL = std::make_shared<RBTreeNode<T>>();
		_TNULL->left = nullptr;
		_TNULL->right = nullptr;
		_root = _TNULL;
	}

public:
    NodePtr find(T key);
    NodePtr insert(T key);
    NodePtr get_root();
    // void remove(T key);

    // NodePtr rbminimum(NodePtr node);
    // NodePtr successor(NodePtr node);
    // NodePtr rbmaximum(NodePtr node);
    // NodePtr predecessor(NodePtr node);
    void print_tree();

private:
    NodePtr _find(NodePtr node, T key);
    NodePtr _insert(NodePtr root, RBTreeNode<T>* parent, T key);
    void _print_tree(NodePtr root, std::string indent, bool last);

    void insert_fix(NodePtr node);
    void linkParentChild(RBTreeNode<T>* parent, NodePtr child);
};

template<typename T>
std::shared_ptr<RBTreeNode<T>> RBTree<T>::get_root() { return _root; }

template<typename T>
std::shared_ptr<RBTreeNode<T>> RBTree<T>::find(T key)
{
    return _find(_root, key);
}

template<typename T>
std::shared_ptr<RBTreeNode<T>> RBTree<T>::_find(NodePtr node, T key)
{
	if (node == _TNULL || key == node->data) {
		return node;
	}

	if (key < node->data) {
		return _find(node->left, key);
	}
	return _find(node->right, key);
}

template<typename T>
std::shared_ptr<RBTreeNode<T>> RBTree<T>::insert(T key) {
	// check if already exists
	NodePtr new_rbnode = find(key);
	if (new_rbnode != _TNULL) return new_rbnode;

	new_rbnode = _insert(_root, nullptr, key);
	insert_fix(new_rbnode);

	return new_rbnode;
}

template<typename T>
std::shared_ptr<RBTreeNode<T>> RBTree<T>::_insert(NodePtr root, RBTreeNode<T>* parent, T key) {
	if (root == _TNULL) {
		NodePtr new_node = std::make_shared<RBTreeNode<T>>();
		new_node->data = key;
		new_node->left = _TNULL;
		new_node->right = _TNULL;
		new_node->parent = parent;
		new_node->color = 1;

        // set as root if first node to insert
		if (parent == nullptr) _root = new_node;
		else linkParentChild(parent, new_node);

		return new_node;
	}

	if (key < root->data) {
		return _insert(root->left, root.get(), key);
	}
	return _insert(root->right, root.get(), key);
}

template<typename T>
void RBTree<T>::linkParentChild(RBTreeNode<T>* parent, NodePtr child) {
	if (child->data < parent->data) {
		parent->left = child;
		return;
	}

	parent->right = child;
}

template<typename T>
void RBTree<T>::insert_fix(NodePtr node) {
	if (node->parent == nullptr) {
		node->color = 0;
		return;
	}
	if (node->parent->parent == nullptr) return;
}

template<typename T>
void RBTree<T>::print_tree() {
    if (_root) {
		_print_tree(_root, "", true);
	}
}

template<typename T>
void RBTree<T>::_print_tree(NodePtr root, std::string indent, bool last) {
	if (root != _TNULL) {
		std::cout << indent;
		if (last) {
		std::cout << "R----";
		indent += "   ";
		} else {
		std::cout << "L----";
		indent += "|  ";
		}

		std::string sColor = root->color ? "RED" : "BLACK";
		std::cout << root->data << "(" << sColor << ")" << std::endl;
		_print_tree(root->left, indent, false);
		_print_tree(root->right, indent, true);
	}
}

#endif // RB_TREE