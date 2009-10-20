/* treenode.h
 *
 * Definition for a keyed tree node.
 */

#ifndef TREENODE_H_
#define TREENODE_H_

#include <cstdlib>

template<class T>
class TreeNode {
    private:
	unsigned long m_key;
	T m_data;

	TreeNode *m_left;
	TreeNode *m_right;

    public:
	TreeNode() {
	    m_key = 0;
	    m_data = 0;

	    m_left = NULL;
	    m_right = NULL;
	}

	TreeNode(unsigned long key, T data) {
	    m_key = key;
	    m_data = data;

	    m_left = NULL;
	    m_right = NULL;
	}

	~TreeNode() {
	    m_left = NULL;
	    m_right = NULL;
	}

	unsigned long & key() {
	    return m_key;
	}

	T &data() {
	    return m_data;
	}

	TreeNode *&left() {
	    return m_left;
	}

	TreeNode *&right() {
	    return m_right;
	}
};

#endif /* TREENODE_H_ */
