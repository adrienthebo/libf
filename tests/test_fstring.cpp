/* test_fstring.cpp
 *
 * Test suite for fstring.
 */


#include <iostream>
#include <cstring>
#include <cassert>
#include "../include/fstring.h"
#include "../include/liblinkedlist.h"


void test_constructor1() {
    FString f1; 

    assert(f1.size() == 0);
}

void test_constructor2() {
    FString f1 = FString("test");

    assert(strcmp(f1.cstring(), "test") == 0);
}

void test_constructor3() {
    FString f1 = FString("testtest", 4);

    assert(f1.size() == 4);
    assert(strcmp(f1.cstring(), "test") == 0);
}

void test_constructor4() {
    FString f1 = FString("test");
    FString copy_fstring = FString(f1);

    assert(f1.size() == copy_fstring.size());
    assert(strcmp(f1.cstring(), copy_fstring.cstring()) == 0);
}

void test_operator_equals() {
    FString f1 = FString("test");
    FString f2 = FString("test");
    FString f3 = FString("toast");

    assert(f1 == f2);
    assert(f1 != f3);
    assert(f2 != f3);
}

void test_tokenize1() {
    FString f1;
    Linkedlist<FString *> f1_tokens = f1.tokenize();
    assert(f1_tokens.size() == 0);
}

void test_tokenize2() {
    FString f2("token");
    Linkedlist<FString *> f2_tokens = f2.tokenize();
    assert(f2_tokens.size() == 1);
    assert(strcmp(f2_tokens.get(0)->cstring(), "token") == 0 );
}

void test_tokenize3() {
    FString f3("token token");
    Linkedlist<FString *> f3_tokens = f3.tokenize();
    assert(f3_tokens.size() == 2);
    assert(strcmp(f3_tokens.get(0)->cstring(), "token") == 0 );
    assert(strcmp(f3_tokens.get(1)->cstring(), "token") == 0 );
}

void test_tokenize4() {
    FString f4("  token1     token2	    token3 token4 t5 tokentoken6");
    Linkedlist<FString *> f4_tokens = f4.tokenize();
    assert(f4_tokens.size() == 6);

    assert(strcmp(f4_tokens.get(0)->cstring(), "token1") == 0 );
    assert(strcmp(f4_tokens.get(1)->cstring(), "token2") == 0 );
    assert(strcmp(f4_tokens.get(2)->cstring(), "token3") == 0 );
    assert(strcmp(f4_tokens.get(3)->cstring(), "token4") == 0 );
    assert(strcmp(f4_tokens.get(4)->cstring(), "t5") == 0 );
    assert(strcmp(f4_tokens.get(5)->cstring(), "tokentoken6") == 0 );
}

void test_token() {
    FString f5("  token1     token2	    token3 token4 t5 tokentoken6");

    assert(strcmp(f5.token(0)->cstring(), "token1") == 0 );
    assert(strcmp(f5.token(1)->cstring(), "token2") == 0 );
    assert(strcmp(f5.token(2)->cstring(), "token3") == 0 );
    assert(strcmp(f5.token(3)->cstring(), "token4") == 0 );
    assert(strcmp(f5.token(4)->cstring(), "t5") == 0 );
    assert(strcmp(f5.token(5)->cstring(), "tokentoken6") == 0 );
    
}

int main(int argc, char **argv) {

    std::cout << "Testing empty constructor." << std::endl;
    test_constructor1();
    std::cout << "Testing cstring constructor." << std::endl;
    test_constructor2();
    std::cout << "Testing bounded cstring constructor." << std::endl;
    test_constructor3();
    std::cout << "Testing copy constructor." << std::endl;
    test_constructor4();

    std::cout << "Testing equivalency operators." << std::endl;
    test_operator_equals();

    std::cout << "Testing tokenize empty string." << std::endl;
    test_tokenize1();
    std::cout << "Testing tokenize single token." << std::endl;
    test_tokenize2();
    std::cout << "Testing tokenize two tokens." << std::endl;
    test_tokenize3();
    std::cout << "Testing tokenize multiple tokens, fugly string." << std::endl;
    test_tokenize4();
    std::cout << "Testing named token." << std::endl;
    test_token();

    std::cout << "If we got this far, then nothing obviously failed..." << std::endl;
    return(EXIT_SUCCESS);
}
