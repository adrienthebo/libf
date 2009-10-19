/* listexception.h
 *
 * Exceptions for liblinkedlist.
 */

#ifndef _LISTEXCEPTION_H_
#define _LISTEXCEPTION_H_
#include <iostream>

class list_index_out_of_bounds {
    private: 
	int m_invalid_index;
    public:
	list_index_out_of_bounds( int invalid_index ) {
	    m_invalid_index = invalid_index;
	}

	void message() {
	    std::cout << "List index " << m_invalid_index << " is out of bounds." << std::endl;
	}

	int invalid_index() {
	    return m_invalid_index;
	}

	friend std::ostream &operator<<(std::ostream & os, list_index_out_of_bounds e) {
	    os << "List index " << e.invalid_index() << " is out of bounds." << std::endl;
	    return os;
	}
};

#endif /* LISTEXCEPTION_H_ */

