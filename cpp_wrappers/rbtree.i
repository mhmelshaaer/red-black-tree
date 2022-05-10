%module rbtree

// required to correctly wrap smart shared pointers
%include <std_shared_ptr.i>

// inform swig about what classes/structs are being
// wrapped in a smart shared pointer
%shared_ptr(RBTreeNode<int>);
%shared_ptr(RBTreeNode<char>);
%shared_ptr(RBTree<int>);
%shared_ptr(RBTree<char>);

// required headers for the rbtree.hpp to compile
%{
#include <iostream>
#include <memory>
%}

// wrap and declare the rbtree.hpp
// equivalent to %{ #include "rbtree.hpp" %}
// followed by %include "rbtree.hpp"
%inline %{
#include "rbtree.hpp"
%}

// instantiating the needed types
%template(int_rbtree_node) RBTreeNode<int>;
%template(char_rbtree_node) RBTreeNode<char>;
%template(int_rbtree) RBTree<int>;
%template(char_rbtree) RBTree<char>;