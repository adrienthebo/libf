/**
 * bst.h
 *
 * Header for a template unbalanced binary search tree
 */

#ifndef BST_H
#define BST_H

#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include "treenode.h"
#include "treeexception.h"

template<class T>
class Bst {
    private:
	TreeNode<T> *m_root;
	int m_size;
	
	//Internal recursive methods
	void r_add(TreeNode<T> *new_node, TreeNode<T> *current_node);
	T & r_get(unsigned long key, TreeNode<T> *current_node) throw(tree_element_not_found);

	//Internal rm helpers
	void rm_no_subtrees(TreeNode<T> *old_node, TreeNode<T> *parent);
	void rm_right_subtree(TreeNode<T> *old_node, TreeNode<T> *parent);
	void rm_left_subtree(TreeNode<T> *old_node, TreeNode<T> *parent);
	void rm_both_subtrees(TreeNode<T> *old_node, TreeNode<T> *parent);

    public:
	Bst();
	~Bst();

	void add(unsigned long key, T data);

	int has(unsigned long key);
	T & get(unsigned long key) throw(tree_element_not_found);

	void rm(unsigned long key) throw(tree_element_not_found);

	void clear();
	bool is_empty();
	int size();
};

#include "../lib/bst.cpp"

#endif /* LIBBST_H_ */

