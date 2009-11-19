
#define BOOST_TEST_MODULE "doubly linked list tests"
#define BOOST_TEST_DYN_LINK 
#include <boost/test/unit_test.hpp>

#include <iostream>

#include "../include/dlinkedlist.h"

BOOST_AUTO_TEST_CASE( test_constructor1 ) {
    std::cout << "Testing default constructor." << std::endl;

    DLinkedlist<int> d1 = DLinkedlist<int>();

    BOOST_CHECK(d1.size() == 0);
}

BOOST_AUTO_TEST_CASE( test_add1 ) {
    std::cout << "Testing add exception cases." << std::endl;

    DLinkedlist<int> d1;

    try {
	d1.add(1, 1);
	BOOST_ERROR("Failed to throw exception on error case.");
    }
    catch (list_index_out_of_bounds e) { }

    try {
	d1.add(1, -1);
	BOOST_ERROR("Failed to throw exception on error case.");
    }
    catch (list_index_out_of_bounds(e)) { }
}

BOOST_AUTO_TEST_CASE( test_add2 ) {
    std::cout << "Testing add." << std::endl;

    DLinkedlist<int> d2;

    d2.add(0, 0);
    BOOST_CHECK(d2.size() == 1);
    d2.add(1, 1);
    BOOST_CHECK(d2.size() == 2);
    d2.add(2, 2);
    BOOST_CHECK(d2.size() == 3);
    d2.add(3, 3);
    BOOST_CHECK(d2.size() == 4);
}

BOOST_AUTO_TEST_CASE( test_add3) {
    std::cout << "Testing appending add." << std::endl;

    DLinkedlist<int> d3;

    d3.add(0);
    d3.add(1);
    d3.add(2);
    d3.add(3);

    BOOST_CHECK(d3.size() == 4);
}

BOOST_AUTO_TEST_CASE( test_get1) {
    std::cout << "Testing get invalid cases." << std::endl;

    DLinkedlist<int> d1;

    for(int i = 0; i < 10; i++) {
	d1.add(i, i);
    }

    try {
	d1.get(-1);
	BOOST_ERROR("Failed to throw exception on error case.");
    }
    catch (list_index_out_of_bounds e) { }
    
    try {
	d1.get(10);
	BOOST_ERROR("Failed to throw exception on error case.");
    }
    catch (list_index_out_of_bounds e) { }
}

BOOST_AUTO_TEST_CASE( test_get2 ) {
    std::cout << "Testing get." << std::endl;
    
    DLinkedlist<int> d2;

    try {
	for(int i = 0; i < 10; i++) {
	    d2.add(i);
	    BOOST_CHECK(d2.get(i) == i);
	}
    }
    catch (list_index_out_of_bounds e) {
	BOOST_ERROR("Threw exception in wrong place.");
    }
}

BOOST_AUTO_TEST_CASE( test_rm1 ) {
    std::cout << "Testing get invalid cases." << std::endl;

    DLinkedlist<int> d1;

    for(int i = 0; i < 10; i++) {
	d1.add(i, i);
    }

    try {
	d1.rm(-1);
	BOOST_ERROR("Failed to throw exception on error case.");
    }
    catch (list_index_out_of_bounds e) { }
    
    try {
	d1.rm(10);
	BOOST_ERROR("Failed to throw exception on error case.");
    }
    catch (list_index_out_of_bounds e) { }
}

BOOST_AUTO_TEST_CASE( test_rm2 ) {
    std::cout << "Testing rm." << std::endl;

    DLinkedlist<int> d2;

    for(int i = 0; i < 10; i++) {
	d2.add(i, i);
    }

    BOOST_CHECK(d2.size() == 10);
    
    d2.rm(9);
    BOOST_CHECK(d2.size() == 9);

    d2.rm(0);
    BOOST_CHECK(d2.size() == 8);
    BOOST_CHECK(d2.get(0) == 1);

    d2.add(0, 0);
    d2.add(9, 9);

    for(int i = 9; i >= 0; i--) {
	d2.rm(0);
	BOOST_CHECK(d2.size() == i);
    }
}

BOOST_AUTO_TEST_CASE( test_assignment_operator) {
    std::cout << "Testing assignment operator." << std::endl;
}
