import rbtree

T = rbtree.int_rbtree()

T.insert(5)
T.insert(3)
T.insert(7)

T.print_tree()

T.remove(5)

T.print_tree()