/* bst.cpp
 *
 * Implementation for a template unbalanced binary search tree
 */

/** 
 * Private helper method to add an element recursively
 *
 * @param new_node the node to add to the tree
 * @param current_node the current working node
 */
template<class T>
void Bst<T>::r_add(TreeNode<T> *new_node, TreeNode<T> *current_node) {
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


/**
 * Private helper method to retrieve an element using recursion
 *
 * @param key the key of the element to retrieve
 * @param current_node the current working node
 */ 
template<class T>
T & Bst<T>::r_get(unsigned long key, TreeNode<T> *current_node) throw(tree_element_not_found) {
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

/**
 * Internal rm helper
 */
template<class T>
void Bst<T>::rm_no_subtrees(TreeNode<T> *old_node, TreeNode<T> *parent) {
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

/**
 * Internal rm helper
 */
template<class T>
void Bst<T>::rm_right_subtree(TreeNode<T> *old_node, TreeNode<T> *parent) {
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

/**
 * Internal rm helper
 */
template<class T>
void Bst<T>::rm_left_subtree(TreeNode<T> *old_node, TreeNode<T> *parent) {
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

/**
 * Internal rm helper
 */
template<class T>
void Bst<T>::rm_both_subtrees(TreeNode<T> *old_node, TreeNode<T> *parent) {
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

/**
 * Default constructor
 */
template<class T>
Bst<T>::Bst() {
    m_root = NULL;
    m_size = 0;
}

/**
 * Destructor
 */
template<class T>
Bst<T>::~Bst() {
    clear();
}

/**
 * public add method
 *
 * @param key The key of the data to add
 * @param data the data to ad
 */
template<class T>
void Bst<T>::add(unsigned long key, T data) {
    TreeNode<T> *new_node = new TreeNode<T>(key, data);
   
    if(m_root == NULL) { //There is no root node, create one.
	m_root = new_node;
    }
    else { //Recursively add node
	r_add(new_node, m_root);
    }

    m_size++;
}

/**
 * Determines whether the element exists in the tree
 *
 * @param key the key that specifies the element to search for
 */
template<class T>
int Bst<T>::has(unsigned long key) {
    bool has = false;
    try {
	r_get(key, m_root);
	has = true;
    }
    catch(tree_element_not_found e) { }

    return has;
}

/**
 * Retrieves the element with the specified key
 *
 * @param key the key that identifies the element
 * @throw tree_element_not_found 
 * @return a reference to the found element
 */
template<class T>
T & Bst<T>::get(unsigned long key) throw(tree_element_not_found) {
    try {
	return r_get(key, m_root);
    }
    catch(tree_element_not_found e) { //Percolate exception
	throw e;
    }

}

/**
 * Removes the element with the specified key
 *
 * @key the key of the element to remove
 * @throw tree_element_not_found
 */
template<class T>
void Bst<T>::rm(unsigned long key) throw(tree_element_not_found) {
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

/**
 * clears the bst
 */
template<class T>
void Bst<T>::clear() {
    while(!is_empty()) {
	rm(m_root->key());
    }
}

template<class T>
bool Bst<T>::is_empty() {
    return m_size == 0;
}

template<class T>
int Bst<T>::size() {
    return m_size;
}


