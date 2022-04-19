#ifndef RB_TREE
#define RB_TREE

#include <iostream>
#include <memory>


template<typename T>
struct RBTreeNode
{
    typedef std::shared_ptr<RBTreeNode> NodePtr;
    // no resource management needed since a node cannot exist without a parent.
    typedef RBTreeNode* ParentPtr;

    T data;
    NodePtr left;
    NodePtr right;
    ParentPtr parent;
    int color = 0;
};

template<typename T>
class RBTree {
private:
    typedef std::shared_ptr<RBTreeNode<T>> NodePtr;
    typedef RBTreeNode<T>* ParentPtr;
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
    NodePtr _insert(NodePtr root, ParentPtr parent, T key);

    void _insert_fix(NodePtr node);
    void _link_parent_child(ParentPtr parent, NodePtr child);
    void _print_tree(NodePtr root, std::string indent, bool last);
	void _rotate_left(NodePtr);
	void _rotate_right(NodePtr);

	bool _is_root(NodePtr);
	bool _is_root(ParentPtr);
};

/********************
 * PUBLIC INTERFACE *
 ********************/

template<typename T>
std::shared_ptr<RBTreeNode<T>> RBTree<T>::get_root() { return _root; }

template<typename T>
std::shared_ptr<RBTreeNode<T>> RBTree<T>::find(T key)
{
    return _find(_root, key);
}

template<typename T>
std::shared_ptr<RBTreeNode<T>> RBTree<T>::insert(T key) {
	// check if already exists
	NodePtr new_rbnode = find(key);
	if (new_rbnode != _TNULL) return new_rbnode;

	new_rbnode = _insert(_root, nullptr, key);
	_insert_fix(new_rbnode);

	return new_rbnode;
}

template<typename T>
void RBTree<T>::print_tree() {
    if (_root) {
		_print_tree(_root, "", true);
	}
}

/*******************
 * PRIVATE HELPERS *
 *******************/

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
std::shared_ptr<RBTreeNode<T>> RBTree<T>::_insert(NodePtr root, ParentPtr parent, T key) {
	if (root == _TNULL) {
		NodePtr new_node = std::make_shared<RBTreeNode<T>>();
		new_node->data = key;
		new_node->left = _TNULL;
		new_node->right = _TNULL;
		new_node->parent = parent;
		new_node->color = 1;

        // set as root if first node to insert
		if (parent == nullptr) _root = new_node;
		else _link_parent_child(parent, new_node);

		return new_node;
	}

	if (key < root->data) {
		return _insert(root->left, root.get(), key);
	}
	return _insert(root->right, root.get(), key);
}

template<typename T>
void RBTree<T>::_link_parent_child(ParentPtr parent, NodePtr child) {
	if (child->data < parent->data) {
		parent->left = child;
		return;
	}

	parent->right = child;
}

template<typename T>
void RBTree<T>::_insert_fix(NodePtr node) {
	if (_is_root(node)) {
		node->color = 0;
		return;
	}

	if (_is_root(node->parent))
	{
		return;
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

template<typename T>
void RBTree<T>::_rotate_left(NodePtr node)
{
	if (node->right == _TNULL) return;

	ParentPtr parent = node->parent;
	NodePtr pivot = node->right;

	pivot->parent = parent;
	if (_is_root(node))
	{
		_root = pivot;
	}
	else if (parent->left == node)
	{
		parent->left = pivot;
	}
	else if (parent->right == node)
	{
		parent->right = pivot;
	}

	node->parent = pivot.get();
	node->right = pivot->left;
	if (node->right != _TNULL)
	{
		node->right->parent = node.get();
	}

	pivot->left = node;
}

template<typename T>
void RBTree<T>::_rotate_right(NodePtr node)
{}

template<typename T>
bool RBTree<T>::_is_root(NodePtr node)
{
	return node->parent == nullptr;
}

template<typename T>
bool RBTree<T>::_is_root(ParentPtr node)
{
	return node->parent == nullptr;
}

#endif // RB_TREE