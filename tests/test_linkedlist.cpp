/* test_linkedlist.cpp 
 *
 * Tests liblinkedlist. See code for documentation, it should be easy 
 * to follow. I hope.
 */

/* Magically create main() and init_unit_test() functions */
#define BOOST_TEST_MODULE "linkedlist main test suite"
/* Specify dynamic linking with test lib */
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <iostream>
#include <fstream>
#include "../include/linkedlist.h"

BOOST_AUTO_TEST_CASE( test_is_empty_stage0) {
    std::cout << "Verifying some basic functions are sane." << std::endl;
    Linkedlist<int> test_linkedlist;
    BOOST_CHECK(test_linkedlist.is_empty());
    BOOST_CHECK(test_linkedlist.size() == 0);
}

/* 
 * This test case tests several functions that are interdependent.
 */
BOOST_AUTO_TEST_CASE( test_core) {
    std::cout << "Testing core functionality." << std::endl;
    Linkedlist<int> test_linkedlist;

    test_linkedlist.add(0, 0);
    BOOST_CHECK(test_linkedlist.size() == 1);

    //Prepend data
    test_linkedlist.add(-1, 0);
    BOOST_CHECK(test_linkedlist.size() == 2);

    //Automatic append data
    test_linkedlist.add(2);
    BOOST_CHECK(test_linkedlist.size() == 3);

    //Bulk add
    for(int i = 3; i < 100; i++) {
	test_linkedlist.add(i);
	BOOST_CHECK(test_linkedlist.size() == i + 1);
    }

    BOOST_CHECK(test_linkedlist.size() == 100);
}

BOOST_AUTO_TEST_CASE( test_get ) {
    std::cout << "Testing retrieval." << std::endl;
    Linkedlist<int> test_linkedlist;

    //Append data
    for(int i = 0; i < 100; i++) 
	test_linkedlist.add(i);

    for(int i = 0; i < 100; i++) 
	BOOST_CHECK(test_linkedlist.get(i) == i);
    
    //Prepend data
    for(int i = -1; i >= -100; i--) 
	test_linkedlist.add(i, 0);

    for(int i = 0, j = -100; i < 100; i++, j++) 
	BOOST_CHECK(test_linkedlist.get(i) == j);
}

BOOST_AUTO_TEST_CASE(test_rm_single) {
    std::cout << "Testing remove." << std::endl;
    Linkedlist<int> test_linkedlist;

    //Append data
    for(int i = 0; i < 100; i++) 
	test_linkedlist.add(i);

    //Remove from tail
    BOOST_CHECK(test_linkedlist.size() == 100);
    BOOST_CHECK(test_linkedlist.get(98) == 98);
    BOOST_CHECK(test_linkedlist.get(99) == 99);
    test_linkedlist.rm(99);

    BOOST_CHECK(test_linkedlist.size() == 99);
    BOOST_CHECK(test_linkedlist.get(98) == 98);

    //Remove from tail again
    test_linkedlist.rm(98);

    BOOST_CHECK(test_linkedlist.size() == 98);
    BOOST_CHECK(test_linkedlist.get(97) == 97);

    //Remove from almost tail
    test_linkedlist.rm(96);

    BOOST_CHECK(test_linkedlist.size() == 97);
    BOOST_CHECK(test_linkedlist.get(95) == 95);
    BOOST_CHECK(test_linkedlist.get(96) == 97);

    //Remove from middle
    BOOST_CHECK(test_linkedlist.get(44) == 44);
    BOOST_CHECK(test_linkedlist.get(45) == 45);
    BOOST_CHECK(test_linkedlist.get(46) == 46);
    test_linkedlist.rm(45);

    BOOST_CHECK(test_linkedlist.size() == 96);
    BOOST_CHECK(test_linkedlist.get(44) == 44);
    BOOST_CHECK(test_linkedlist.get(45) == 46);
    BOOST_CHECK(test_linkedlist.get(46) == 47);

    //Remove from almost head
    BOOST_CHECK(test_linkedlist.get(0) == 0);
    BOOST_CHECK(test_linkedlist.get(1) == 1);
    BOOST_CHECK(test_linkedlist.get(2) == 2);

    test_linkedlist.rm(1);
    BOOST_CHECK(test_linkedlist.size() == 95);
    BOOST_CHECK(test_linkedlist.get(0) == 0);
    BOOST_CHECK(test_linkedlist.get(1) == 2);
    BOOST_CHECK(test_linkedlist.get(2) == 3);

    //Remove from head
    test_linkedlist.rm(0);
    BOOST_CHECK(test_linkedlist.size() == 94);
    BOOST_CHECK(test_linkedlist.get(0) == 2);
    BOOST_CHECK(test_linkedlist.get(1) == 3);

    //Remove from head again
    test_linkedlist.rm(0);
    BOOST_CHECK(test_linkedlist.size() == 93);
    BOOST_CHECK(test_linkedlist.get(0) == 3);
    BOOST_CHECK(test_linkedlist.get(1) == 4);
}

BOOST_AUTO_TEST_CASE(test_large_dataset) {
    std::cout << "Testing a very large dataset. This could take a while." << std::endl;
    const int dataset_size = 1000;
    Linkedlist<int> test_linkedlist;

    for(int i = 1; i <= dataset_size; i++) {
	test_linkedlist.add(i);
    }

    BOOST_CHECK(test_linkedlist.size() == dataset_size);

    for(int i = 1; i <= dataset_size; i++) {
	BOOST_CHECK(test_linkedlist.get(0) == i);
	test_linkedlist.rm(0);
    }

    BOOST_CHECK(test_linkedlist.size() == 0);
    BOOST_CHECK(test_linkedlist.is_empty());
}

BOOST_AUTO_TEST_CASE( test_exceptions ) {
    std::cout << "Testing exception throwing and handling." << std::endl;

    Linkedlist<int> test_linkedlist;

    //test add()
    try {
	test_linkedlist.add(0, -1);
	BOOST_ERROR("Failed to throw exception on invalid position.");
    }
    catch ( list_index_out_of_bounds e) {}
    try {
	test_linkedlist.add(0, 1);
	BOOST_ERROR("Failed to throw exception on invalid position.");
    }
    catch ( list_index_out_of_bounds e) {}

    //test get()
    try {
	test_linkedlist.get(-1);
	BOOST_ERROR("Failed to throw exception on invalid position.");
    }
    catch ( list_index_out_of_bounds e) {}
    try {
	test_linkedlist.get(0);
	BOOST_ERROR("Failed to throw exception on invalid position.");
    }
    catch ( list_index_out_of_bounds e) {}
    try {
	test_linkedlist.get(1);
	BOOST_ERROR("Failed to throw exception on invalid position.");
    }
    catch ( list_index_out_of_bounds e) {}

    //test rm()
    try {
	test_linkedlist.rm(-1);
	BOOST_ERROR("Failed to throw exception on invalid position.");
    }
    catch ( list_index_out_of_bounds e) {}
    try {
	test_linkedlist.rm(0);
	BOOST_ERROR("Failed to throw exception on invalid position.");
    }
    catch ( list_index_out_of_bounds e) {}
    try {
	test_linkedlist.rm(1);
	BOOST_ERROR("Failed to throw exception on invalid position.");
    }
    catch ( list_index_out_of_bounds e) {}
}
