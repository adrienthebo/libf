
#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H

#include "dnode.h"
#include "listexception.h"

template<class T>
class DLinkedlist {
    private:
	DNode<T> *m_head;
	DNode<T> *m_tail;

	unsigned int m_size;

	void connect(DNode<T> *prev, DNode<T> *next) {
	    prev->next() = next;
	    next->prev() = prev;
	}

    public:
	/* Default constructor
	 *
	 * Creates an empty dlinkedlist
	 */
	DLinkedlist() {
	    m_head = new DNode<T>();
	    m_tail = new DNode<T>();
	    connect(m_head, m_tail);

	    m_size = 0;
	}

	/* Destructor
	 *
	 * Deallocates all dnodes.
	 */
	~DLinkedlist() {
	    DNode<T> *current_node = m_head;
	    DNode<T> *delete_node;

	    while(current_node != NULL) {
		delete_node = current_node;
		current_node = current_node->next();

		delete delete_node;
	    }	

	    m_size = 0;
	}
	
	/* size()
	 * 
	 * @return the number of elements stored in the list.
	 */
	int size() {
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
	void add(T data, int position) throw(list_index_out_of_bounds) {
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
	void add(T data) throw(list_index_out_of_bounds) {
	    add(data, m_size);
	}

	/** 
	 * Retrieves the template data at the index specified by position
	 *
	 * @param position the index of the data to retrieve
	 *
	 * @throws list_index_out_of_bounds if position is out of bounds
	 */
	T & get(int position) {
	    if(position < 0 || (unsigned int)position >= m_size) {
		throw list_index_out_of_bounds(position);
	    }

	    DNode<T> *current_node = m_head->next();
	    for(int i = 0; i < position; i++) {
		current_node = current_node->next();
	    }

	    return current_node->data();
	}

	/**
	 * Removes the template data specified by position
	 *
	 * @param position the index of the data to remove
	 *
	 * @throw list_index_out_of_bounds if position is ound of bounds
	 */
	void rm(int position) throw(list_index_out_of_bounds) {
	    if(position < 0 || (unsigned int)position >= m_size) {
		throw list_index_out_of_bounds(position);
	    }

	    //Find node to delete
	    DNode<T> *to_delete = m_head->next();

	    for(int i = 0; i < position; i++) {
		to_delete = to_delete->next();
	    }

	    connect(to_delete->prev(), to_delete->next());
	    m_size--;
	}
};

#endif
