/* treexception.h
 *
 * Tree exceptions. Exceptional trees?
 */

#ifndef _TREEEXCEPTION_H_
#define _TREEEXCEPTION_H_

#include <iostream>

class tree_element_not_found {
    private:
	unsigned long m_element_key;
    public:
	tree_element_not_found( unsigned long element_key) {
	    m_element_key = element_key;
	}
    
	void message() {
	    std::cout << *this << std::endl;
	}

	unsigned int element_key() {
	    return m_element_key;
	}

	friend std::ostream &operator<<(std::ostream & os, tree_element_not_found e) {
	    os << "No element with key " << e.element_key() << " exists in the tree.";
	}
};

#endif /* _TREEEXCEPTION_H_ */

