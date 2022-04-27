%module rbtree
%include <iostream>
%include <memory>
%inline %{

#include <rbtree.hpp>

%}

%include <rbtree.hpp>

%template(int_rbtree) RBTree<int>;
%template(char_rbtree) RBTree<char>;