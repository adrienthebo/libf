/* node.h 
 *
 * Node definition for liblinkedlist. Nothing interesting here.
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

	T get_data() {
	    return m_data;
	}

	void set_data(T data) {
	    m_data = data;
	}
	
	Node *get_next() {
	    return m_next;
	}

	void set_next(Node *next) {
	    m_next = next;
	}
};

#endif /* NODE_H_ */

