/* liblinkedlist.h 
 * "Interface" for a linkedlist. Coming from Java makes a header file being
 * and interface a bit strange.
 */
#ifndef LIBLINKEDLIST_H_
#define LIBLINKEDLIST_H_

#include "node.h"
#include "listexception.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

template<class T>
class Linkedlist {
    private:
	Node<T> *m_head;
	/* Size is tracked instead of being dynamically calculated because
	 * large linked lists really bog down when iterating over the entire
	 * list. Makes more sense to keep track of this instead of recounting.
	 */
	int m_size; 
    public:
	Linkedlist() {
	    m_head = NULL;
	    m_size = 0;
	}

	~Linkedlist() {
	    Node<T> *current_node = m_head;

	    while(current_node != NULL) {
		Node<T> *next_node = current_node->get_next();
		
		delete current_node;

		current_node = next_node;
	    }
	    m_head = NULL;
	}

	/* Inserts the data at the specified position */
	void add(T data, int position) throw(list_index_out_of_bounds) {
	    // Bounds check
	    if( position < 0 || position > m_size)
		throw list_index_out_of_bounds(position);
	    

	    if(m_size == 0 || position == 0) { 
		m_head = new Node<T>(data, m_head);
	    }
	    else {
		Node<T> *current_node = m_head;
		for(int i = 0; i + 1 < position; i++) //Locate node before insertion
		    current_node = current_node->get_next();
		
		current_node->set_next(new Node<T>(data, current_node->get_next()));
	    }
	    m_size++;
	}

	/* Appends data to the end of the list */
	void add(T data) throw(list_index_out_of_bounds) {
	    add(data, m_size);
	}

	/* Retrieves the node specified at position */
	T get(int position) throw(list_index_out_of_bounds) {
	    if(position < 0 || position >= m_size) 
		throw list_index_out_of_bounds(position);

	    Node<T> *current_node = m_head;
	    for(int i = 0; i < position; i++) {
		current_node = current_node->get_next();
	    }
	    
	    if(current_node == NULL) 
		throw "Critical error; null pointer found where no null pointer should be!";

	    return current_node->get_data();
	}

	/* Removes the node specified by position */
	void rm(int position) throw(list_index_out_of_bounds) {
	    if(position < 0 || position >= m_size) 
		throw list_index_out_of_bounds(position);
	    
	    if(position == 0) {
		Node<T> *to_delete = m_head;
		m_head = to_delete->get_next();

		delete to_delete;
	    }
	    else {
		Node<T> *current_node = m_head;
		for(int i = 0; i + 1 < position; i++) {
		    current_node = current_node->get_next();
		}
		
		if(current_node == NULL) 
		    throw "Critical error; null pointer found where no null pointer should be!";

		Node<T> *to_delete = current_node->get_next();
		current_node->set_next(to_delete->get_next());
		delete to_delete;
	    }
	    m_size--;
	}

	bool is_empty() {
	    return m_size == 0;
	}
	int size() {
	    return m_size;
	}

	void freeze( std::ofstream & output ) {
	    for(int i = 0; i < m_size; i++) {
		output << get(i) << '\n';
	    }
	}
	void thaw( std::ifstream & input ) {
	    while(!input.eof() ) {
		std::string instring;
		input >> instring;
		if(instring.length() > 0) 
		    add(atoi(instring.c_str()));
	    }
	}

	friend std::ostream &operator<< (std::ostream & os, Linkedlist<T> & list) {
	    for(int i = 0; i < list.m_size; i++) {
		os << list.get(i);

		if(i + 1 < list.m_size) 
		    os << ", ";
	    }
	    return os;
	}
};


#endif /* LIBLINKEDLIST_H_ */
