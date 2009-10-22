/* test_fstring.cpp
 *
 * Test suite for fstring.
 */

/* magic */
#define BOOST_TEST_MODULE "fstring main test suite"
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <iostream>
#include <cstring>
#include "../include/fstring.h"
#include "../include/liblinkedlist.h"


BOOST_AUTO_TEST_CASE( test_constructor1 ) {
    std::cout << "Testing empty constructor." << std::endl;
    FString f1; 

    BOOST_CHECK(f1.size() == 0);
}

BOOST_AUTO_TEST_CASE( test_constructor2 ) {
    std::cout << "Testing cstring constructor." << std::endl;
    FString f1 = FString("test");

    BOOST_CHECK(strcmp(f1.cstring(), "test") == 0);
}

BOOST_AUTO_TEST_CASE( test_constructor3 ) {
    std::cout << "Testing bounded cstring constructor." << std::endl;
    FString f1 = FString("testtest", 4);

    BOOST_CHECK(f1.size() == 4);
    BOOST_CHECK(strcmp(f1.cstring(), "test") == 0);
}

BOOST_AUTO_TEST_CASE( test_constructor4 ) {
    std::cout << "Testing copy constructor." << std::endl;
    FString f1 = FString("test");
    FString copy_fstring = FString(f1);

    BOOST_CHECK(f1.size() == copy_fstring.size());
    BOOST_CHECK(strcmp(f1.cstring(), copy_fstring.cstring()) == 0);
}

BOOST_AUTO_TEST_CASE( test_operator_equals ) {
    std::cout << "Testing equivalency operators." << std::endl;
    FString f1 = FString("test");
    FString f2 = FString("test");
    FString f3 = FString("toast");

    BOOST_CHECK(f1 == f2);
    BOOST_CHECK(f1 != f3);
    BOOST_CHECK(f2 != f3);
}

BOOST_AUTO_TEST_CASE( test_tokenize1 ) {
    std::cout << "Testing tokenize empty string." << std::endl;
    FString f1;
    Linkedlist<FString *> f1_tokens = f1.tokenize();
    BOOST_CHECK(f1_tokens.size() == 0);
}

BOOST_AUTO_TEST_CASE( test_tokenize2 ) {
    std::cout << "Testing tokenize single token." << std::endl;
    FString f2("token");
    std::cout << "f2 stuff:\"" << f2 << "\"" << std::endl;
    Linkedlist<FString *> f2_tokens = f2.tokenize();
    BOOST_CHECK(f2_tokens.size() == 1);
    std::cout << "f2->cstring() stuff: \"" << f2_tokens.get(0)->cstring() << "\"" << std::endl;
    BOOST_CHECK(strcmp(f2_tokens.get(0)->cstring(), "token") == 0 );
}

BOOST_AUTO_TEST_CASE( test_tokenize3 ) {
    std::cout << "Testing tokenize two tokens." << std::endl;
    FString f3("token token");
    Linkedlist<FString *> f3_tokens = f3.tokenize();
    BOOST_CHECK(f3_tokens.size() == 2);
    BOOST_CHECK(strcmp(f3_tokens.get(0)->cstring(), "token") == 0 );
    BOOST_CHECK(strcmp(f3_tokens.get(1)->cstring(), "token") == 0 );
}

BOOST_AUTO_TEST_CASE( test_tokenize4 ) {
    std::cout << "Testing tokenize multiple tokens, fugly string." << std::endl;
    FString f4("  token1     token2	    token3 token4 t5 tokentoken6");
    Linkedlist<FString *> f4_tokens = f4.tokenize();
    BOOST_CHECK(f4_tokens.size() == 6);

    BOOST_CHECK(strcmp(f4_tokens.get(0)->cstring(), "token1") == 0 );
    BOOST_CHECK(strcmp(f4_tokens.get(1)->cstring(), "token2") == 0 );
    BOOST_CHECK(strcmp(f4_tokens.get(2)->cstring(), "token3") == 0 );
    BOOST_CHECK(strcmp(f4_tokens.get(3)->cstring(), "token4") == 0 );
    BOOST_CHECK(strcmp(f4_tokens.get(4)->cstring(), "t5") == 0 );
    BOOST_CHECK(strcmp(f4_tokens.get(5)->cstring(), "tokentoken6") == 0 );
}

BOOST_AUTO_TEST_CASE( test_token ) {
    std::cout << "Testing named token." << std::endl;
    FString f5("  token1     token2	    token3 token4 t5 tokentoken6");

    BOOST_CHECK(strcmp(f5.token(0)->cstring(), "token1") == 0 );
    BOOST_CHECK(strcmp(f5.token(1)->cstring(), "token2") == 0 );
    BOOST_CHECK(strcmp(f5.token(2)->cstring(), "token3") == 0 );
    BOOST_CHECK(strcmp(f5.token(3)->cstring(), "token4") == 0 );
    BOOST_CHECK(strcmp(f5.token(4)->cstring(), "t5") == 0 );
    BOOST_CHECK(strcmp(f5.token(5)->cstring(), "tokentoken6") == 0 );
    
}

BOOST_AUTO_TEST_CASE( test_concat1 ) {
    std::cout << "Testing concatenate two strings." << std::endl;

    FString f1 = FString("token1");
    FString f2 = FString("token2");
    
    f1.concat( f2 );

    FString f3 = FString("token1token2");
    BOOST_CHECK(f1 == f3);
}

BOOST_AUTO_TEST_CASE( test_concat2 ) {
    std::cout << "Testing concatentate multiple strings." << std::endl;

    FString f1 = FString("token1");
    FString f2 = FString(" token2 ");
    FString f3 = FString("!!!TOKEN3!!!");
    FString f4 = FString("     ");
 
    FString f5 = FString("token1 token2 !!!TOKEN3!!!     ");

    f1.concat( f2 ).concat( f3 ).concat( f4 );
    
    BOOST_CHECK(f1 == f5);
}
