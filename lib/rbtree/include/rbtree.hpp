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

	enum class node_color { RED, BLACK };

    T data;
    NodePtr left;
    NodePtr right;
    ParentPtr parent;
    node_color color = node_color::BLACK;
};

template<typename T>
class RBTree {
private:
    typedef RBTreeNode<T> Node;
    typedef typename Node::node_color NodeColor;
    typedef std::shared_ptr<RBTreeNode<T>> NodePtr;
    typedef RBTreeNode<T>* ParentPtr;
    typedef RBTreeNode<T>* RawNodePtr;
	NodePtr _root;
	NodePtr _TNULL;

public:
	RBTree() {
		_TNULL = std::make_shared<Node>();
		_TNULL->left = nullptr;
		_TNULL->right = nullptr;
		_root = _TNULL;
	}

public:
    NodePtr find(T key);
    NodePtr insert(T key);
    NodePtr get_root();

	bool is_terminal(NodePtr);
    // void remove(T key);

    // NodePtr rbminimum(NodePtr node);
    // NodePtr successor(NodePtr node);
    // NodePtr rbmaximum(NodePtr node);
    // NodePtr predecessor(NodePtr node);
    void print_tree();

private:
    NodePtr _find(NodePtr node, T key);
    NodePtr _insert(NodePtr root, ParentPtr parent, T key);
	NodePtr _get_sibling(ParentPtr);

    void _insert_fix(NodePtr node);
    void _link_parent_child(ParentPtr parent, NodePtr child);
    void _print_tree(NodePtr root, std::string indent, bool last);
	void _rotate_left(NodePtr);
	void _rotate_right(NodePtr);

	// balance states
	/**
	 * @brief Node parent sibling is colored red.
	 * 
	 * @param node NodePtr.
	 */
	void _fix_state00(NodePtr node);
	/**
	 * @brief Node parent sibling is colored black.
	 * 
	 * @param node NodePtr.
	 */
	void _fix_state01(NodePtr node);

	/**
	 * @brief Node parent sibling is colored black and
	 * 		requires a single rotation-- i.e. the straight line case.
	 * 
	 * @param node NodePtr.
	 */
	void _fix_state10(NodePtr node);

	/**
	 * @brief Node parent sibling is colored black and
	 * 		requires a double rotation-- i.e. the triangle case.
	 * 
	 * @param node NodePtr.
	 */
	void _fix_state11(NodePtr node);

	void _switch_color(RawNodePtr);

	bool _is_root(NodePtr);
	bool _is_root(RawNodePtr);
	bool _is_state10(RawNodePtr);
};

/********************
 * PUBLIC INTERFACE *
 ********************/

template<typename T>
std::shared_ptr<RBTreeNode<T>> RBTree<T>::get_root() { return _root; }

template<typename T>
bool RBTree<T>::is_terminal(NodePtr node)
{
	return node == _TNULL;
}

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
		NodePtr new_node = std::make_shared<Node>();
		new_node->data = key;
		new_node->left = _TNULL;
		new_node->right = _TNULL;
		new_node->parent = parent;
		new_node->color = NodeColor::RED;

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
std::shared_ptr<RBTreeNode<T>> RBTree<T>::_get_sibling(ParentPtr node)
{
	if (_is_root(node))
	{
		return nullptr;
	}

	if (node->parent->left.get() == node)
	{
		return node->parent->right;
	}

	return node->parent->left;
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
		node->color = NodeColor::BLACK;
		return;
	}

	if (_is_root(node->parent) || node->parent->color == NodeColor::BLACK)
	{
		return;
	}

	// get the parent sibling node--i.e. uncle.
	NodePtr parent_sibling = _get_sibling(node->parent);

	if (parent_sibling->color == NodeColor::RED)
	{
		// state 00: a parent sibling is red
		_fix_state00(node);
	}
	else
	{
		// state 01: a parent sibling is black
		_fix_state01(node);
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

		std::string sColor = root->color == NodeColor::RED ? "RED" : "BLACK";
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
{
	if (node->left == _TNULL) return;

	ParentPtr parent = node->parent;
	NodePtr pivot = node->left;

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
	node->left = pivot->right;
	if (node->left != _TNULL)
	{
		node->left->parent = node.get();
	}

	pivot->right = node;
}

template<typename T>
void RBTree<T>::_fix_state00(NodePtr node)
{
	NodePtr grand_parent = find(node->parent->parent->data);
	NodePtr parent = grand_parent->left.get() == node->parent
		? grand_parent->left
		: grand_parent->right;
	NodePtr parent_sibling = _get_sibling(parent.get());

	parent->color = NodeColor::BLACK;
	parent_sibling->color = NodeColor::BLACK;
	grand_parent->color = NodeColor::RED;

	_insert_fix(grand_parent);
}

template<typename T>
void RBTree<T>::_fix_state01(NodePtr node)
{
	if (_is_state10(node.get()))
	{
		// single rotation
		return _fix_state10(node);
	}
	
	// double rotation
	_fix_state11(node);
}

template<typename T>
void RBTree<T>::_fix_state10(NodePtr node)
{
	NodePtr grand_parent = find(node->parent->parent->data);

	if (grand_parent->left->left == node)
	{
		_rotate_right(grand_parent);
	}
	else
	{
		_rotate_left(grand_parent);
	}

	// recolor parent and grandparent
	_switch_color(node->parent);
	_switch_color(grand_parent.get());
}

template<typename T>
void RBTree<T>::_fix_state11(NodePtr node)
{
	NodePtr grand_parent = find(node->parent->parent->data);
	NodePtr parent;

	if (grand_parent->left->right == node)
	{
		parent = grand_parent->left;
		_rotate_left(grand_parent->left);
	}
	else
	{
		parent = grand_parent->right;
		_rotate_right(grand_parent->right);
	}

	_fix_state10(parent);
}

template<typename T>
void RBTree<T>::_switch_color(RawNodePtr node)
{
	if (node->color == NodeColor::RED)
	{
		node->color = NodeColor::BLACK;
		return;
	}

	node->color = NodeColor::RED;
}

template<typename T>
bool RBTree<T>::_is_root(NodePtr node)
{
	return node->parent == nullptr;
}

template<typename T>
bool RBTree<T>::_is_root(RawNodePtr node)
{
	return node->parent == nullptr;
}

template<typename T>
bool RBTree<T>::_is_state10(RawNodePtr node)
{
	ParentPtr grand_parent = node->parent->parent;
	return grand_parent->left->left.get() == node
		|| grand_parent->right->right.get() == node;
}

#endif // RB_TREE