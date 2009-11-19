/**
 * Definition for a template doubly linked list
 */

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

	void connect(DNode<T> *prev, DNode<T> *next);

    public:
	DLinkedlist(); 
	DLinkedlist(const DLinkedlist & copy_linkedlist);
	~DLinkedlist();

	DLinkedlist<T> & operator=(const DLinkedlist & copy_linkedlist);
	
	int size() const;

	void add(T data, int position) throw(list_index_out_of_bounds);
	void add(T data) throw(list_index_out_of_bounds); 

	T & get(int position) const; 

	void rm(int position) throw(list_index_out_of_bounds);
	void clear();
};

#include "../lib/dlinkedlist.cpp"

#endif
