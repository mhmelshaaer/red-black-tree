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

    void remove(T key);
    void print_tree();

	bool is_terminal(NodePtr);

private:
	/**
	 * @brief Perform a BST find operation.
	 * 
	 * @param node subtree root.
	 * @param key key to search for.
	 * @return NodePtr 
	 */
    NodePtr _find(NodePtr root, T key);

	/**
	 * @brief Perform a BST insertion operation.
	 * 
	 * @param root subtree root
	 * @param parent parent of the current subtree root.
	 * @param key Key to be inserted
	 * @return NodePtr The inserted node.
	 */
    NodePtr _insert(NodePtr root, ParentPtr parent, T key);

	/**
	 * @brief Perform a BST deletion operation.
	 * 
	 * @param root subtree root
	 * @param parent parent of the current subtree root.
	 * @param key Key to be deleted
	 * @return NodePtr The BST Replacement.
	 */
    NodePtr _remove(NodePtr root, NodePtr parent, T key);

	NodePtr _get_sibling(ParentPtr);
	NodePtr _get_single_child(NodePtr);

    NodePtr _successor(NodePtr node);
    NodePtr _rbminimum(NodePtr node);
    NodePtr _predecessor(NodePtr node);
    NodePtr _rbmaximum(NodePtr node);

	/**
	 * @brief Fix red-black tree imbalance after insertion.
	 * 
	 * @param node The newly inserted node.
	 */
    void _insert_fix(NodePtr node);
	/**
	 * @brief Fix the tree **AFTER** BST deletion.
	 * 
	 * @param u The BST Replacement node. The actual deleted node.
	 * 		Usually, it will be one of the following two possibilities.
	 * 			1- u := v successor/predecessor.
	 * 			2. u := _TNULL with parent pointer set to the v->parent.
	 * 		Anywhere in the code, if you found a node named "u", then
	 * 		this is the BST Replacment node.
	 * @param v The node that was required to be deleted. This node is 
	 * 		no longer part of the red-black tree at that moment.
	 */
    void _remove_fix(NodePtr u, NodePtr v);
	
    void _link_parent_child(ParentPtr parent, NodePtr child);
    void _print_tree(NodePtr root, std::string indent, bool last);
	void _rotate_left(NodePtr);
	void _rotate_right(NodePtr);
	void _swap_node(NodePtr, NodePtr);


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

	/**
	 * @brief If the deleted node or the 
	 * 		replacement node is RED.
	 * 
	 */
	void _remove_fix_state000(NodePtr);

	/**
	 * @brief If both the deleted and the replacement
	 * 		nodes are black.
	 * 
	 */
	void _remove_fix_state001(NodePtr);

	/**
	 * @brief If both the deleted and the replacement
	 * 		nodes are black and sibling node is black.
	 * 
	 */
	void _remove_fix_state010(NodePtr);

	/**
	 * @brief If both the deleted and the replacement
	 * 		nodes are black and sibling node is black
	 * 		with at least a red child.
	 * 
	 */
	void _remove_fix_state011(NodePtr);

	/**
	 * @brief If both the deleted and the replacement
	 * 		nodes are black and sibling node is black
	 * 		with all black children. Black, Black
	 * 		everywhere.
	 * 
	 */
	void _remove_fix_state100(NodePtr);

	/**
	 * @brief If both the deleted and the replacement
	 * 		nodes are black and sibling node is red.
	 * 
	 */
	void _remove_fix_state101(NodePtr);

	void _switch_color(RawNodePtr);

	bool _is_root(NodePtr);
	bool _is_root(RawNodePtr);
	bool _is_state10(RawNodePtr);
	bool _is_remove_fix_state000(NodePtr, NodePtr);
    bool _has_two_child(NodePtr node);
    bool _has_red_child(NodePtr node);
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
void RBTree<T>::remove(T key)
{
	// check if exists
	NodePtr v = find(key);
	if (v == _TNULL) return;

	NodePtr u = _remove(_root, nullptr, key);
	_remove_fix(u, v);
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
std::shared_ptr<RBTreeNode<T>> RBTree<T>::_remove(NodePtr root, NodePtr parent, T key)
{
	if (root->data == key && _has_two_child(root))
	{
		NodePtr u = _successor(root);
		_swap_node(root, u);
		return _remove(root->right, root, u->data);
	}
	if (root->data == key)
	{
		NodePtr u = _get_single_child(root);
		if (parent->left == root)
		{
			parent->left = u;
		}
		else
		{
			parent->right = u;
		}

		u->parent = parent.get();

		return u;
	}

	if (key < root->data)
	{
		return _remove(root->left, root, key);
	}

	return _remove(root->right, root, key);
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
std::shared_ptr<RBTreeNode<T>> RBTree<T>::_get_single_child(NodePtr node)
{
	if (!is_terminal(node->left))
	{
		return node->left;
	}
	return node->right;
}

template<typename T>
std::shared_ptr<RBTreeNode<T>> RBTree<T>::_rbminimum(NodePtr node)
{
	NodePtr min_node = node;
	while(!is_terminal(min_node->left)) min_node = min_node->left;
	return min_node;
}

template<typename T>
std::shared_ptr<RBTreeNode<T>> RBTree<T>::_successor(NodePtr node)
{
	if (!is_terminal(node->right))
	{
		return _rbminimum(node->right);
	}
	else if (_is_root(node))
	{
		return _TNULL;
	}
	else if (node->parent->left == node)
	{
		return find(node->parent->data);
	}
	else
	{
		RawNodePtr itr = node.get();
		while(!_is_root(itr) && itr->parent->right.get() == itr) itr = itr->parent;
		return _is_root(itr) ? _TNULL : find(itr->parent->data);
	}
}

template<typename T>
std::shared_ptr<RBTreeNode<T>> RBTree<T>::_rbmaximum(NodePtr node)
{
	NodePtr max_node = node;
	while(!is_terminal(max_node->right)) max_node = max_node->right;
	return max_node;
}

template<typename T>
std::shared_ptr<RBTreeNode<T>> RBTree<T>::_predecessor(NodePtr node)
{
	if (!is_terminal(node->left))
	{
		return _rbmaximum(node->left);
	}
	else if (_is_root(node))
	{
		return _TNULL;
	}
	else if (node->parent->right == node)
	{
		return find(node->parent->data);
	}
	else
	{
		RawNodePtr itr = node.get();
		while(!_is_root(itr) && itr->parent->left.get() == itr) itr = itr->parent;
		return _is_root(itr) ? _TNULL : find(itr->parent->data);
	}
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
void RBTree<T>::_remove_fix(NodePtr u, NodePtr v)
{
	if (_is_remove_fix_state000(u, v)) {
		return _remove_fix_state000(u);
	}

	_remove_fix_state001(u);
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
void RBTree<T>::_swap_node(NodePtr v, NodePtr u)
{
	if (is_terminal(u))
	{
		return;
	}
	std::swap(v->data, u->data);
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
void RBTree<T>::_remove_fix_state000(NodePtr u)
{
	u->color = NodeColor::BLACK;
}

template<typename T>
void RBTree<T>::_remove_fix_state001(NodePtr u)
{
	NodePtr sibling = _get_sibling(u.get());

	if (sibling->color == NodeColor::BLACK)
	{
		return _remove_fix_state010(u);
	}

	_remove_fix_state101(u);
}

template<typename T>
void RBTree<T>::_remove_fix_state010(NodePtr u)
{
	NodePtr sibling = _get_sibling(u.get());

	if (_has_red_child(sibling))
	{
		return _remove_fix_state011(u);
	}

	_remove_fix_state100(u);
}

template<typename T>
void RBTree<T>::_remove_fix_state011(NodePtr u)
{
	NodePtr parent = find(u->parent->data);
	NodePtr sibling = _get_sibling(u.get());
	NodePtr red_child;

	if (parent->right == sibling && sibling->right->color == NodeColor::RED)
	{
		// sibling is parent right child and the red node is on sibling right
		// hence RR case.
		red_child = sibling->right;
		_rotate_left(parent);
	}
	else if (parent->right == sibling)
	{
		// sibling is parent right child and the red node is on sibling left
		// hence RL case.
		red_child = sibling->left;
		_rotate_right(sibling);
		_rotate_left(parent);
	}
	else if (sibling->left->color == NodeColor::RED)
	{
		// sibling is parent left child and the red node is on sibling left
		// hence LL case
		red_child = sibling->left;
		_rotate_right(parent);
	}
	else
	{
		// LR case
		red_child = sibling->right;
		_rotate_left(sibling);
		_rotate_right(parent);
	}

	// color the sibling the original parent color.
	sibling->color = parent->color;

	// color the parent and the doubl-black node to black
	parent->color = NodeColor::BLACK;
	u->color = NodeColor::BLACK;
	red_child->color = NodeColor::BLACK;
}

template<typename T>
void RBTree<T>::_remove_fix_state100(NodePtr u)
{
	// base case in case the recoloring required recursive fix.
	if (_is_root(u.get()))
	{
		return;
	}

	NodePtr parent = find(u->parent->data);
	NodePtr sibling = _get_sibling(u.get());

	// color u black and sibling red
	u->color = NodeColor::BLACK;
	sibling->color = NodeColor::RED;

	if (_is_root(parent.get()) || parent->color == NodeColor::RED)
	{
		parent->color = NodeColor::BLACK;
		return;
	}

	// parent becomes double black, fix it.
	_remove_fix_state100(parent);
}

template<typename T>
void RBTree<T>::_remove_fix_state101(NodePtr u)
{
	// u is red, u->parent is black, then rotate u->parent
	// in the opposite direction of u. Then _remove_fix_state010(u)
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

template<typename T>
bool RBTree<T>::_is_remove_fix_state000(NodePtr u, NodePtr v)
{
	return u->color == NodeColor::RED || v->color == NodeColor::RED;
}

template<typename T>
bool RBTree<T>::_has_two_child(NodePtr node)
{
	return !is_terminal(node->left) && !is_terminal(node->right);
}

template<typename T>
bool RBTree<T>::_has_red_child(NodePtr node)
{
	return node->left->color == NodeColor::RED ||
		node->right->color == NodeColor::RED;
}

#endif // RB_TREE