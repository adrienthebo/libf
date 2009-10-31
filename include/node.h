/* node.h 
 *
 * Definition for a node in a linear linked list.
 */
#ifndef NODE_H_
#define NODE_H_

#include <cstdlib>

template <class T>
class Node {

    private:
	T m_data;
	Node *m_next;
    public:
	Node() {
	    m_data = NULL;
	    m_next = NULL;
	}

	Node(T data) {
	    m_data = data;
	    m_next = NULL;
	}

	Node(T data, Node *next) {
	    m_data = data;
	    m_next = next;
	}

	~Node() {
	    m_next = NULL;
	}

	T & data() {
	    return m_data;
	}
	
	Node *& next() {
	    return m_next;
	}
};

#endif /* NODE_H_ */

