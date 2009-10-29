/* test_fstring.cpp
 *
 * Test suite for fstring.
 */

/* magic */
#define BOOST_TEST_MODULE "fstring main test suite"
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <iostream>
#include <sstream>

#include <cstring>
#include <string>

#include "../include/fstring.h"
#include "../include/linkedlist.h"


BOOST_AUTO_TEST_CASE( test_constructor1 ) {
    std::cout << "Testing empty constructor." << std::endl;

    FString f1; 

    BOOST_CHECK(f1.size() == 0);
}

BOOST_AUTO_TEST_CASE( test_constructor2 ) {
    std::cout << "Testing cstring constructor." << std::endl;

    FString f1 = FString("test");

    BOOST_CHECK(f1.size() == 4);
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
    FString copy_fstring(f1);

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
    Linkedlist<FString *> f2_tokens = f2.tokenize();

    BOOST_CHECK(f2_tokens.size() == 1);
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

BOOST_AUTO_TEST_CASE( test_concat1_fstring ) {
    std::cout << "Testing concatenate two fstrings." << std::endl;

    FString f1 = FString("token1");
    FString f2 = FString("token2");
    
    f1.concat( f2 );

    FString f3 = FString("token1token2");
    BOOST_CHECK(f1 == f3);
}

BOOST_AUTO_TEST_CASE( test_concat2_fstring ) {
    std::cout << "Testing concatenate multiple fstrings." << std::endl;

    FString f1 = FString("token1");
    FString f2 = FString(" token2 ");
    FString f3 = FString("!!!TOKEN3!!!");
    FString f4 = FString("     ");
 
    FString f5 = FString("token1 token2 !!!TOKEN3!!!     ");

    f1.concat( f2 ).concat( f3 ).concat( f4 );
    
    BOOST_CHECK(f1 == f5);
}

BOOST_AUTO_TEST_CASE( test_concat1_cstring ) {
    std::cout << "Testing concatenate fstring and cstring." << std::endl;

    FString f1 = FString("token1");
    const char *c1 = "token2";
    
    f1.concat( c1 );

    FString f2 = FString("token1token2");
    BOOST_CHECK(f1 == f2);
}

BOOST_AUTO_TEST_CASE( test_concat2_cstring ) {
    std::cout << "Testing concatenate fstring and multiple cstrings." << std::endl;

    FString f1 = FString("token1");
    const char *c2 = " token2 ";
    const char *c3 = "!!!TOKEN3!!!";
    const char *c4 = "     ";
 
    FString f2= FString("token1 token2 !!!TOKEN3!!!     ");

    f1.concat( c2 ).concat( c3 ).concat( c4 );
    
    BOOST_CHECK(f1 == f2);
}

BOOST_AUTO_TEST_CASE( test_concat3_char) {
    std::cout << "Testing concatenate fstring and char." << std::endl;

    FString f1 = FString("token");
    FString f2 = FString("token1");
    char c = '1';

    f1.concat(c);

    BOOST_CHECK(f1.size() == 6);
    BOOST_CHECK(f1 == f2);
}

BOOST_AUTO_TEST_CASE( test_clear ) {
    std::cout << "Testing clear." << std::endl;
    
    FString f1("token1 token2 token3    token4		token5");
    FString f2;

    f1.clear();
    f2.clear();

    BOOST_CHECK(f1.size() == 0);
    BOOST_CHECK(f2.size() == 0);

}

BOOST_AUTO_TEST_CASE( test_extraction1 ) {
    std::cout << "Testing extraction operator with empty string." << std::endl;

    std::istringstream input_stream;
    FString f1;
    FString f2;

    input_stream.str() = "";
    input_stream >> f1;

    BOOST_CHECK(f1.size() == 0);
    BOOST_CHECK(f1 == f2);
}

BOOST_AUTO_TEST_CASE( test_extraction2) {
    std::cout << "Testing extraction operator with simple string." << std::endl;

    std::istringstream input_stream;
    FString f3;
    FString f4 = FString("token1");

    input_stream.str("token1");
    input_stream >> f3;

    BOOST_CHECK(f3.size() == 6);
    BOOST_CHECK(f3 == f4);
}

BOOST_AUTO_TEST_CASE( test_extraction3) {
    std::cout << "Testing extraction operator with more complex string." << std::endl;

    std::istringstream input_stream;
    FString f5;
    FString f6 = FString("token1 token2");

    input_stream.str("token1 token2");
    input_stream >> f5;

    BOOST_CHECK(f5.size() == 13);
    BOOST_CHECK(f5 == f6);
}

BOOST_AUTO_TEST_CASE( test_extraction4 ) {
    std::cout << "Testing extraction operator with even more complex string." << std::endl;

    std::istringstream input_stream;
    FString f7;
    FString f8 = FString("token1 token2 token3 token4");

    input_stream.str("token1 token2 token3 token4");
    input_stream >> f7;

    BOOST_CHECK(f7.size() == 27 );
    BOOST_CHECK(f7 == f8);
}

BOOST_AUTO_TEST_CASE( test_extraction5 ) {
    std::cout << "Testing extraction operator with fugly string." << std::endl;

    std::istringstream input_stream;
    FString f9;
    FString f10 = FString("   token1 token2  token3	token4 token5  ");

    input_stream.str("   token1 token2  token3	token4 token5  ");
    input_stream >> f9;

    BOOST_CHECK(f9.size() == 40);
    BOOST_CHECK(f9 == f10);
}

BOOST_AUTO_TEST_CASE( test_assignment_operator1 ) {
    std::cout << "Testing empty assignment operator" << std::endl;

    FString f1;
    FString f2;
    FString f3 = FString("token1");

    f2 = f1;
    f3 = f1;

    BOOST_CHECK(f1.size() == 0);
    BOOST_CHECK(f2.size() == 0);
    BOOST_CHECK(f3.size() == 0);
    BOOST_CHECK(f1 == f2);
    BOOST_CHECK(f1 == f3);
}

BOOST_AUTO_TEST_CASE( test_assignment_operator2 ) {
    std::cout << "Testing assignment operator." << std::endl;

    FString f1 = FString("token1");
    FString f2 = FString("token2 token3");

    f1 = f2;

    BOOST_CHECK(f1.size() == 13);
    BOOST_CHECK(f1 == f2);
}
