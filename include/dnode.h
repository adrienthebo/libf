/* dnode.h
 * 
 * Definition for a doubly linked node. It's basically a glorified struct.
 *
 */

#ifndef DNODE_H
#define DNODE_H

#include <cstdlib>

template <class T>
class DNode {

    private:
	T *m_data;
	DNode *m_prev;
	DNode *m_next;

    public:
	
	//Default constructor
	DNode<T>() {
	    m_data = NULL;
	    m_prev = NULL;
	    m_next = NULL;
	}

	//Deep copy constructor
	DNode<T>(const DNode<T> & n) {
	    m_data = new T(*(n.m_data));
	    m_prev = n.m_prev;
	    m_next = n.m_next;
	}
	
	DNode<T>(T data) {
	    m_data = new T(data);
	    m_prev = NULL;
	    m_next = NULL;
	}

	~DNode() {
	    delete(m_data);
	    m_prev = NULL;
	    m_next = NULL;
	}
	    
	T *& data() {
	    return m_data;
	}

	DNode *& prev() {
	    return m_prev;
	}

	DNode *& next() {
	    return m_next;
	}
};
#endif
