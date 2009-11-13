/* linkedlist.h 
 * Implements a template linear linked list.
 */
#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include "node.h"
#include "listexception.h"
#include <cstdlib>
#include <iostream>

template<class T>
class Linkedlist {
    private:
	Node<T> *m_head;
	int m_size; 
    public:

	Linkedlist<T>();
	~Linkedlist(); 

	void add(T data, int position) throw(list_index_out_of_bounds);
	void add(T data) throw(list_index_out_of_bounds);
	 
	T & get(int position) throw(list_index_out_of_bounds);

	void rm(int position) throw(list_index_out_of_bounds);

	bool is_empty();
	int size();

	friend std::ostream &operator<< (std::ostream & os, Linkedlist<T> & list) {
	    for(int i = 0; i < list.m_size; i++) {
		os << list.get(i);

		if(i + 1 < list.m_size) 
		    os << ", ";
	    }
	    return os;
	}
};

#include "../lib/linkedlist.cpp"

#endif /* LIBLINKEDLIST_H_ */


