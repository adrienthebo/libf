/* test_bst.cpp
 *
 * Test suite for bst.
 */

#define BOOST_TEST_MODULE "bst test module"
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <iostream>
#include "../include/bst.h"

BOOST_AUTO_TEST_CASE( test_sanity ) {
    std::cout << "Verifying some basic functions are sane." << std::endl;

    Bst<int> test_bst;
    
    BOOST_CHECK(test_bst.is_empty());
    BOOST_CHECK(test_bst.size() == 0);
}

BOOST_AUTO_TEST_CASE( test_core ) {
    std::cout << "Testing core functionality." << std::endl;

    Bst<int> test_bst;

    //add root
    test_bst.add(4, 4);
    BOOST_CHECK(!test_bst.is_empty());
    BOOST_CHECK(test_bst.size() == 1);
    BOOST_CHECK(test_bst.has(4));
    BOOST_CHECK(test_bst.get(4) == 4);

    //Add left
    test_bst.add(2, 2);
    BOOST_CHECK(test_bst.has(2));
    BOOST_CHECK(test_bst.get(2) == 2);
    BOOST_CHECK(test_bst.size() == 2);
    
    //Add right
    test_bst.add(6, 6);
    BOOST_CHECK(test_bst.has(6));
    BOOST_CHECK(test_bst.get(6) == 6);
    BOOST_CHECK(test_bst.size() == 3);

    //Add left to left subtree
    test_bst.add(1, 1);
    BOOST_CHECK(test_bst.has(1));
    BOOST_CHECK(test_bst.get(1) == 1);
    BOOST_CHECK(test_bst.size() == 4);

    //Add right to left subtree 
    test_bst.add(3, 3);
    BOOST_CHECK(test_bst.has(3));
    BOOST_CHECK(test_bst.get(3) == 3);
    BOOST_CHECK(test_bst.size() == 5);
    
    //Add left to right subtree
    test_bst.add(5, 5);
    BOOST_CHECK(test_bst.has(5));
    BOOST_CHECK(test_bst.get(5) == 5);
    BOOST_CHECK(test_bst.size() == 6);

    //Add right to right subtree
    test_bst.add(7, 7);
    BOOST_CHECK(test_bst.has(7));
    BOOST_CHECK(test_bst.get(7) == 7);
    BOOST_CHECK(test_bst.size() == 7);
    
    //Bulk add
    for(int i = 8; i < 20; i++) {
	test_bst.add(i, i);
	BOOST_CHECK(test_bst.has(i));
	BOOST_CHECK(test_bst.get(i) == i);
	BOOST_CHECK(test_bst.size() == i);
    }
}

BOOST_AUTO_TEST_CASE( test_rm_no_subtrees1 ) {
    std::cout << "Testing rm_no_subtrees() case 1" << std::endl;

    //Delete root
    Bst<int> test_bst;
    test_bst.add(0, 0);

    test_bst.rm(0);
    BOOST_CHECK(!test_bst.has(0));
    BOOST_CHECK(test_bst.is_empty());
}

BOOST_AUTO_TEST_CASE( test_rm_no_subtrees2 ) {
    std::cout << "Testing rm_no_subtrees() case 2" << std::endl;
    
    //Delete right leaf
    Bst<int> test_bst2; 
    test_bst2.add(0, 0);
    test_bst2.add(1, 1);

    test_bst2.rm(1);
    BOOST_CHECK(test_bst2.has(0));
    BOOST_CHECK(!test_bst2.has(1));
    BOOST_CHECK(test_bst2.size() == 1);
}

BOOST_AUTO_TEST_CASE( test_rm_no_subtrees3 ) {
    std::cout << "Testing rm_no_subtrees() case 3" << std::endl;

    //Delete left leaf
    Bst<int> test_bst3;
    test_bst3.add(2, 2);
    test_bst3.add(1, 1);

    test_bst3.rm(1);
    BOOST_CHECK(test_bst3.has(2));
    BOOST_CHECK(!test_bst3.has(1));
    BOOST_CHECK(test_bst3.size() == 1);
}

BOOST_AUTO_TEST_CASE( test_rm_right_subtree1 ) {
    std::cout << "Testing rm_right_subtree() case 1" << std::endl;
    
    //Delete root with right leaf
    Bst<int> test_bst;
    
    test_bst.add(0, 0);
    test_bst.add(1, 1);

    test_bst.rm(0);
    BOOST_CHECK(test_bst.size() == 1);
    BOOST_CHECK(!test_bst.has(0));
    BOOST_CHECK(test_bst.has(1));
}

BOOST_AUTO_TEST_CASE( test_rm_right_subtree2 ) {
    std::cout << "Testing rm_right_subtree() case 2" << std::endl;
    
    //Delete root with subtree
    Bst<int> test_bst2;

    test_bst2.add(0, 0);
    test_bst2.add(1, 1);
    test_bst2.add(2, 2);

    test_bst2.rm(0);
    BOOST_CHECK(test_bst2.size() == 2);
    BOOST_CHECK(!test_bst2.has(0));
    BOOST_CHECK(test_bst2.has(1));
    BOOST_CHECK(test_bst2.has(2));
}

BOOST_AUTO_TEST_CASE( test_rm_right_subtree3 ) {
    std::cout << "Testing rm_right_subtree() case 3" << std::endl;
	
    //Delete subtree with subtree
    Bst<int> test_bst3;

    test_bst3.add(0, 0);
    test_bst3.add(1, 1);
    test_bst3.add(2, 2);

    test_bst3.rm(1);
    BOOST_CHECK(test_bst3.size() == 2);
    BOOST_CHECK(test_bst3.has(0));
    BOOST_CHECK(!test_bst3.has(1));
    BOOST_CHECK(test_bst3.has(2));
}

BOOST_AUTO_TEST_CASE( test_rm_left_subtree1 ) {
    std::cout << "Testing rm_left_subtree() case 1" << std::endl;

    //Delete root with left leaf
    
    Bst<int> test_bst;

    test_bst.add(1, 1);
    test_bst.add(0, 0);

    test_bst.rm(1);
    BOOST_CHECK(test_bst.size() == 1);
    BOOST_CHECK(!test_bst.has(1));
    BOOST_CHECK(test_bst.has(0));
}
    
BOOST_AUTO_TEST_CASE( test_rm_left_subtree2 ) {
    std::cout << "Testing rm_left_subtree() case 2" << std::endl;
	
    //Delete root with subtree
    Bst<int> test_bst2;

    test_bst2.add(2, 2);
    test_bst2.add(1, 1);
    test_bst2.add(0, 0);

    test_bst2.rm(2);
    BOOST_CHECK(test_bst2.size() == 2);
    BOOST_CHECK(!test_bst2.has(2));
    BOOST_CHECK(test_bst2.has(1));
    BOOST_CHECK(test_bst2.has(0));
}

BOOST_AUTO_TEST_CASE( test_rm_left_subtree3 ) {
    std::cout << "Testing rm_left_subtree() case 3" << std::endl;

    //Delete subtree with subtree
    
    Bst<int> test_bst3;

    test_bst3.add(2, 2);
    test_bst3.add(1, 1);
    test_bst3.add(0, 0);

    test_bst3.rm(1);
    BOOST_CHECK(test_bst3.size() == 2);
    BOOST_CHECK(test_bst3.has(2));
    BOOST_CHECK(!test_bst3.has(1));
    BOOST_CHECK(test_bst3.has(0));
}

BOOST_AUTO_TEST_CASE( test_rm_both_subtrees1) {
    std::cout << "Testing rm_both_subtrees() case 1" << std::endl;

    //remove root with two leaves
    Bst<int> test_bst;

    test_bst.add(1, 1);
    test_bst.add(0, 0);
    test_bst.add(2, 2);

    test_bst.rm(1);
    BOOST_CHECK(test_bst.size() == 2);
    BOOST_CHECK(!test_bst.has(1));
    BOOST_CHECK(test_bst.has(0));
    BOOST_CHECK(test_bst.has(2));

    test_bst.rm(0);
    BOOST_CHECK(test_bst.size() == 1);
    BOOST_CHECK(!test_bst.has(1));
    BOOST_CHECK(!test_bst.has(0));
    BOOST_CHECK(test_bst.has(2));

    test_bst.rm(2);
    BOOST_CHECK(test_bst.is_empty());
    BOOST_CHECK(!test_bst.has(1));
    BOOST_CHECK(!test_bst.has(0));
    BOOST_CHECK(!test_bst.has(2));
}
    
BOOST_AUTO_TEST_CASE( test_rm_both_subtrees2) {
    std::cout << "Testing rm_both_subtrees() case 2" << std::endl;
    
    //Remove root with subtrees
    Bst<int> test_bst2;

    test_bst2.add(4, 4);
    test_bst2.add(2, 2);
    test_bst2.add(6, 6);
    test_bst2.add(1, 1);
    test_bst2.add(3, 3);
    test_bst2.add(5, 5);
    test_bst2.add(7, 7);
    
    test_bst2.rm(4);

    BOOST_CHECK(test_bst2.size() == 6);
    BOOST_CHECK(!test_bst2.has(4));
    BOOST_CHECK(test_bst2.has(2));
    BOOST_CHECK(test_bst2.has(6));
    BOOST_CHECK(test_bst2.has(1));
    BOOST_CHECK(test_bst2.has(3));
    BOOST_CHECK(test_bst2.has(5));
    BOOST_CHECK(test_bst2.has(7));
}

BOOST_AUTO_TEST_CASE( test_rm_both_subtrees3) {
    std::cout << "Testing rm_both_subtrees() case 3" << std::endl;

    //Remove root of left subtree
    Bst<int> test_bst3;

    test_bst3.add(4, 4);
    test_bst3.add(2, 2);
    test_bst3.add(6, 6);
    test_bst3.add(1, 1);
    test_bst3.add(3, 3);
    test_bst3.add(5, 5);
    test_bst3.add(7, 7);

    test_bst3.rm(2);

    BOOST_CHECK(test_bst3.size() == 6);
    BOOST_CHECK(test_bst3.has(4));
    BOOST_CHECK(!test_bst3.has(2));
    BOOST_CHECK(test_bst3.has(6));
    BOOST_CHECK(test_bst3.has(1));
    BOOST_CHECK(test_bst3.has(3));
    BOOST_CHECK(test_bst3.has(5));
    BOOST_CHECK(test_bst3.has(7));
}

BOOST_AUTO_TEST_CASE( test_rm_both_subtrees4) {
    std::cout << "Testing rm_both_subtrees() case 4" << std::endl;

    //Remove root of left subtree
    Bst<int> test_bst4;

    test_bst4.add(4, 4);
    test_bst4.add(2, 2);
    test_bst4.add(6, 6);
    test_bst4.add(1, 1);
    test_bst4.add(3, 3);
    test_bst4.add(5, 5);
    test_bst4.add(7, 7);

    test_bst4.rm(6);

    BOOST_CHECK(test_bst4.size() == 6);
    BOOST_CHECK(test_bst4.has(4));
    BOOST_CHECK(test_bst4.has(2));
    BOOST_CHECK(!test_bst4.has(6));
    BOOST_CHECK(test_bst4.has(1));
    BOOST_CHECK(test_bst4.has(3));
    BOOST_CHECK(test_bst4.has(5));
    BOOST_CHECK(test_bst4.has(7));
}
    
BOOST_AUTO_TEST_CASE( test_rm_both_subtrees5) {
    std::cout << "Testing rm_both_subtrees() case 5" << std::endl;
    //Remove root of right subtree
    Bst<int> test_bst5;

    test_bst5.add(4, 4);
    test_bst5.add(2, 2);
    test_bst5.add(6, 6);
    test_bst5.add(1, 1);
    test_bst5.add(3, 3);
    test_bst5.add(5, 5);
    test_bst5.add(7, 7);

    test_bst5.rm(6);

    BOOST_CHECK(test_bst5.size() == 6);
    BOOST_CHECK(test_bst5.has(4));
    BOOST_CHECK(test_bst5.has(2));
    BOOST_CHECK(!test_bst5.has(6));
    BOOST_CHECK(test_bst5.has(1));
    BOOST_CHECK(test_bst5.has(3));
    BOOST_CHECK(test_bst5.has(5));
    BOOST_CHECK(test_bst5.has(7));
}

BOOST_AUTO_TEST_CASE( test_rm_both_subtrees6) {
    std::cout << "Testing rm_both_subtrees() case 6" << std::endl;

    //Remove root till no nodes remain
    Bst<int> test_bst6;

    test_bst6.add(4, 4);
    test_bst6.add(2, 2);
    test_bst6.add(6, 6);
    test_bst6.add(1, 1);
    test_bst6.add(3, 3);
    test_bst6.add(5, 5);
    test_bst6.add(7, 7);

    test_bst6.rm(4);
    BOOST_CHECK(test_bst6.size() == 6);
    BOOST_CHECK(!test_bst6.has(4));
    BOOST_CHECK(test_bst6.has(2));
    BOOST_CHECK(test_bst6.has(6));
    BOOST_CHECK(test_bst6.has(1));
    BOOST_CHECK(test_bst6.has(3));
    BOOST_CHECK(test_bst6.has(5));
    BOOST_CHECK(test_bst6.has(7));

    test_bst6.rm(3);
    BOOST_CHECK(test_bst6.size() == 5);
    BOOST_CHECK(!test_bst6.has(4));
    BOOST_CHECK(test_bst6.has(2));
    BOOST_CHECK(test_bst6.has(6));
    BOOST_CHECK(test_bst6.has(1));
    BOOST_CHECK(!test_bst6.has(3));
    BOOST_CHECK(test_bst6.has(5));
    BOOST_CHECK(test_bst6.has(7));

    test_bst6.rm(2);
    BOOST_CHECK(test_bst6.size() == 4);
    BOOST_CHECK(!test_bst6.has(4));
    BOOST_CHECK(!test_bst6.has(2));
    BOOST_CHECK(test_bst6.has(6));
    BOOST_CHECK(test_bst6.has(1));
    BOOST_CHECK(!test_bst6.has(3));
    BOOST_CHECK(test_bst6.has(5));
    BOOST_CHECK(test_bst6.has(7));

    test_bst6.rm(1);
    BOOST_CHECK(test_bst6.size() == 3);
    BOOST_CHECK(!test_bst6.has(4));
    BOOST_CHECK(!test_bst6.has(2));
    BOOST_CHECK(test_bst6.has(6));
    BOOST_CHECK(!test_bst6.has(1));
    BOOST_CHECK(!test_bst6.has(3));
    BOOST_CHECK(test_bst6.has(5));
    BOOST_CHECK(test_bst6.has(7));

    test_bst6.rm(6);
    BOOST_CHECK(test_bst6.size() == 2);
    BOOST_CHECK(!test_bst6.has(4));
    BOOST_CHECK(!test_bst6.has(2));
    BOOST_CHECK(!test_bst6.has(6));
    BOOST_CHECK(!test_bst6.has(1));
    BOOST_CHECK(!test_bst6.has(3));
    BOOST_CHECK(test_bst6.has(5));
    BOOST_CHECK(test_bst6.has(7));

    test_bst6.rm(5);
    BOOST_CHECK(test_bst6.size() == 1);
    BOOST_CHECK(!test_bst6.has(4));
    BOOST_CHECK(!test_bst6.has(2));
    BOOST_CHECK(!test_bst6.has(6));
    BOOST_CHECK(!test_bst6.has(1));
    BOOST_CHECK(!test_bst6.has(3));
    BOOST_CHECK(!test_bst6.has(5));
    BOOST_CHECK(test_bst6.has(7));

    test_bst6.rm(7);
    BOOST_CHECK(test_bst6.size() == 0);
    BOOST_CHECK(test_bst6.is_empty());
    BOOST_CHECK(!test_bst6.has(4));
    BOOST_CHECK(!test_bst6.has(2));
    BOOST_CHECK(!test_bst6.has(6));
    BOOST_CHECK(!test_bst6.has(1));
    BOOST_CHECK(!test_bst6.has(3));
    BOOST_CHECK(!test_bst6.has(5));
    BOOST_CHECK(!test_bst6.has(7));
}

BOOST_AUTO_TEST_CASE( test_duplicate_keys) {
    std::cout << "Testing behavior on duplicate keys." << std::endl;
    /* expected behavior: adding duplicate keys stomp on preexisting keys.
     * It seems more rational to replace keys instead of throwing 
     * exceptions left and right.
     */

    Bst<int> test_bst = Bst<int>();
    test_bst.add(1, 1);
    test_bst.add(1, 2);
    
    BOOST_CHECK(test_bst.size() == 1);
    BOOST_CHECK(test_bst.get(1) == 2);
}

