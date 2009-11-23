/** 
 * Implementation for a doubly linked list
 */

/** 
 * private connector method
 */
template<class T>
void DLinkedlist<T>::connect(DNode<T> *prev, DNode<T> *next) {
    prev->next() = next;
    next->prev() = prev;
}

/**
 * Default constructor
 *
 * Creates an empty dlinkedlist
 */
template<class T>
DLinkedlist<T>::DLinkedlist() {
    m_head = new DNode<T>();
    m_tail = new DNode<T>();
    connect(m_head, m_tail);

    m_size = 0;
}

template<class T>
DLinkedlist<T>::DLinkedlist(const DLinkedlist & copy_linkedlist) {
    m_head = new DNode<T>();
    m_tail = new DNode<T>();
    connect(m_head, m_tail);

    m_size = 0;

    for(int i = 0; i < copy_linkedlist.size(); i++ ) {
	add(copy_linkedlist.get(i));
    }
}

/**
 * Destructor
 *
 * Deallocates all dnodes.
 */
template<class T>
DLinkedlist<T>::~DLinkedlist() {
    DNode<T> *current_node = m_head;
    DNode<T> *delete_node;

    while(current_node != NULL) {
	delete_node = current_node;
	current_node = current_node->next();

	delete delete_node;
    }	

    m_size = 0;
}

/**
 * size()
 * 
 * @return the number of elements stored in the list.
 */
template<class T>
int DLinkedlist<T>::size() const {
    return m_size;
}

/** 
 * Adds data to the list at the specified position
 *
 * @param data the template data to add
 * @param position the position to add the data
 *
 * @throws list_index_out_of_bounds if position is out of bounds
 */
template<class T>
void DLinkedlist<T>::add(T data, int position) throw(list_index_out_of_bounds) {
    if(position < 0 || (unsigned int)position > m_size) {
	throw list_index_out_of_bounds(position);
    }
    
    DNode<T> *new_node = new DNode<T>(data);
    DNode<T> *prev_node = m_head;
    DNode<T> *next_node;

    for(int i = 0; i < position; i++ ) {
	prev_node = prev_node->next();
    }
    
    next_node = prev_node->next();
    connect(prev_node, new_node);
    connect(new_node, next_node);

    m_size++;

}

/** 
 * Appends data to the list 
 *
 * @param data the template data to add
 *
 * @throws list_index_out_of_bounds if position is out of bounds
 */
template<class T>
void DLinkedlist<T>::add(T data) throw(list_index_out_of_bounds) {
    add(data, m_size);
}

/** 
 * Retrieves the template data at the index specified by position
 *
 * @param position the index of the data to retrieve
 *
 * @throws list_index_out_of_bounds if position is out of bounds
 */
template<class T>
T & DLinkedlist<T>::get(int position) const {
    if(position < 0 || (unsigned int)position >= m_size) {
	throw list_index_out_of_bounds(position);
    }

    DNode<T> *current_node = m_head->next();
    for(int i = 0; i < position; i++) {
	current_node = current_node->next();
    }

    return *(current_node->data());
}

/**
 * Removes the template data specified by position
 *
 * @param position the index of the data to remove
 *
 * @throw list_index_out_of_bounds if position is ound of bounds
 */
template<class T>
void DLinkedlist<T>::rm(const int position) throw(list_index_out_of_bounds) {
    if(position < 0 || (unsigned int)position >= m_size) {
	throw list_index_out_of_bounds(position);
    }

    //Find node to delete
    DNode<T> *to_delete = m_head->next();

    for(int i = 0; i < position; i++) {
	to_delete = to_delete->next();
    }

    connect(to_delete->prev(), to_delete->next());
    delete(to_delete);
    m_size--;
}

template<class T>
void DLinkedlist<T>::clear() {
    while(size() != 0) {
	rm(0);
    }
}

template<class T>
DLinkedlist<T> & DLinkedlist<T>::operator=(const DLinkedlist & copy_linkedlist) {
    
    clear();

    DNode<T> *curr = copy_linkedlist.m_head->next();

    while(curr != copy_linkedlist.m_tail) {
	add(*(curr->data()));

	curr = curr->next();
    }

    return *this;
}

