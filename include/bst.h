/* bst.h
 *
 * Implementation for a template unbalanced binary search tree
 */

#ifndef BST_H_
#define BST_H_

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
	void r_add(TreeNode<T> *new_node, TreeNode<T> *current_node) {
	    if(new_node->key() > current_node->key()) { //Right subtree
		if(current_node->right() != NULL) { //Recurse onto right subtree
		    r_add(new_node, current_node->right());
		}
		else { //No right subtree, append.
		    current_node->right() = new_node; 
		}
	    }
	    else if (new_node->key() < current_node->key()) { //Left subtree
		if(current_node->left() != NULL) { //Recurse onto left subtree
		    r_add(new_node, current_node->left());
		}
		else { //New left subtree, append.
		    current_node->left() = new_node;
		}
	    }
	    else { //Duplicate key
		current_node->data() = new_node->data();
		//Remove extra node, and decrement size since add() will increment it.
		delete new_node;
		m_size--;
	    }
	}

	T r_get(unsigned long key, TreeNode<T> *current_node) throw(tree_element_not_found) {
	    if(current_node == NULL) {
		throw tree_element_not_found(key);
	    }

	    if(current_node->key() < key) { //Key is greater than current node, recurse right
		return r_get(key, current_node->right());
	    }
	    else if(current_node->key() > key) { //Key is less than current node, recurse left
		return r_get(key, current_node->left());
	    }
	    else { //Key is same as this node, return data
		return current_node->data();
	    }
	}

	//Internal rm helpers
	void rm_no_subtrees(TreeNode<T> *old_node, TreeNode<T> *parent) {
	    if(parent == NULL) { //Parent is null, old_node is root.
		m_root = NULL;
	    }
	    else if(parent->left() == old_node) { //Delete left child
		parent->left() = NULL;
	    }
	    else { //Delete right child
		parent->right() = NULL;
	    }
	}

	void rm_right_subtree(TreeNode<T> *old_node, TreeNode<T> *parent) {
	    if(parent == NULL) { //Parent is null, old_node is root.
		m_root = old_node->right();
	    }
	    else if(parent->left() == old_node) { //old_node is left child. Attach old_node's right subtree to parent
		parent->left() = old_node->right();
	    }
	    else { //old_node is right child. Attach old_node's right subtree to parent
		parent->right() = old_node->right();
	    }
	}

	void rm_left_subtree(TreeNode<T> *old_node, TreeNode<T> *parent) {
	    if(parent == NULL) { //Parent is null, old_node is root.
		m_root = old_node->left();
	    }
	    else if(parent->left() == old_node) { //old_node is left child. Attach old_node's left subtree to parent
		parent->left() = old_node->left();
	    }
	    else { //old_node is right child. Attach old node's right subtree to parent
		parent->right() = old_node->left();
	    }
	}

	void rm_both_subtrees(TreeNode<T> *old_node, TreeNode<T> *parent) {
	    //Find rightmost node in left subtree
	    TreeNode<T> *rightmost_node = old_node->left();
	    TreeNode<T> *rightmost_node_parent = old_node;
	    while(rightmost_node->right() != NULL) {
		rightmost_node_parent = rightmost_node;
		rightmost_node = rightmost_node->right();
	    }

	    if(old_node->left() == rightmost_node) { //Rightmost_node is child of old_node
		//TODO does anything need to actually happen?
	    }
	    else {
		/* Reattach rightmost_node's left children to parent
		 * And attach old_node's left subtree to rightmost_node.
		 */
		rightmost_node_parent->right() = rightmost_node->left();
		rightmost_node->left() = old_node->left();
	    }

	    rightmost_node->right() = old_node->right(); //
	    
	    if(parent == NULL) { //old_node is root
		m_root = rightmost_node;
	    }
	    else { //old_node is child
		if(parent->left() == old_node) { //old_node is left child
		    parent->left() = rightmost_node;
		}
		else { //old_node is right child
		    parent->right() = rightmost_node;
		}
	    }
	}

	int size_by_count(TreeNode<T> *current_node);
	void print(TreeNode<T> *current_node);
    public:
	Bst() {
	    m_root = NULL;
	    m_size = 0;
	}
	~Bst() {
	    clear();
	}

	void add(unsigned long key, T data) {
	    TreeNode<T> *new_node = new TreeNode<T>(key, data);
	   
	    if(m_root == NULL) { //There is no root node, create one.
		m_root = new_node;
	    }
	    else { //Recursively add node
		r_add(new_node, m_root);
	    }

	    m_size++;
	}

	int has(unsigned long key) {
	    bool has = false;
	    try {
		r_get(key, m_root);
		has = true;
	    }
	    catch(tree_element_not_found e) { }

	    return has;
	}

	T get(unsigned long key) throw(tree_element_not_found) {
	    T return_data;
	    try {
		return_data = r_get(key, m_root);
	    }
	    catch(tree_element_not_found e) { //Percolate exception
		throw e;
	    }

	    return return_data;
	}

	void rm(unsigned long key) throw(tree_element_not_found) {
	    TreeNode<T> *old_node = m_root;
	    TreeNode<T> *parent = NULL;

	    //Locate node
	    while(old_node != NULL && old_node->key() != key) {
		parent = old_node;
		if(key > old_node->key()) { //Key is bigger than current node, check right subtree
		    old_node = old_node->right();
		} 
		else { //Key is smaller than current node, check left subtree
		    old_node = old_node->left();
		}
	    }

	    if(old_node == NULL) { //No node with specified key exists.
		throw tree_element_not_found(key);
	    }
	    else if(old_node->right() == NULL && old_node->left() == NULL) { //No subtrees
		rm_no_subtrees(old_node, parent);
	    }
	    else if(old_node->right() != NULL && old_node->left() == NULL) { //Right subtree
		rm_right_subtree(old_node, parent);
	    }
	    else if(old_node->right() == NULL && old_node->left() != NULL) { //Left subtree
		rm_left_subtree(old_node, parent);
	    }
	    else {
		rm_both_subtrees(old_node, parent);
	    }

	    delete old_node;
	    m_size--;
	}

	void clear() {
	    while(!is_empty()) {
		rm(m_root->key());
	    }
	}

	bool is_empty() {
	    return m_size == 0;
	}

	int size() {
	    return m_size;
	}
};

#endif /* LIBBST_H_ */

