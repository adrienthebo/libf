/* 
 * Defines a string class based off of a char array.
 *
 * Huge [expletive] caveat - we have to make sure to allocate an extra space 
 * for the null terminator, or horrible ungodly bugs will crop up and cause
 * us to lose thousands of years of our lives digging through glibc backtraces.
 */
#include "../include/fstring.h"
#include <cstring>

//Default constructor
FString::FString() {
    m_string = new char[1];
    *m_string = '\0';
    m_length = 0;
}

//cstring constructor
FString::FString(const char *c_string) {
    m_length = strlen(c_string);
    m_string = new char[m_length + 1];

    strncpy(m_string, c_string, m_length);
    *(m_string + m_length) = '\0'; // Make abso-*******-lutely sure the string is null terminated.
}

//Copy constructor
FString::FString(const FString & f) {
    m_length = f.m_length;
    m_string = new char[m_length + 1];

    strncpy(m_string, f.m_string, m_length + 1);
}

//Bounded cstring constructor (only copy (int)length elements)
FString::FString(const char *c_string, const unsigned int length) {
    m_length = length;
    m_string = new char[m_length + 1];

    strncpy(m_string, c_string, m_length);
    *(m_string + m_length) = '\0';
}

//Array destructor
FString::~FString() {
    delete [] m_string;
}  

int FString::size() const {
    return m_length;
}

//Returns a cstring copy of the fstring
char *FString::cstring() const {
    char *c_string = new char[ m_length + 1 ]; //Grab the null pointer and copy that too

    strncpy(c_string, m_string, m_length + 1);

    return c_string;
}

//Yaaaay operator overloading
bool FString::operator==(const FString & f) const {
    return strcmp(m_string, f.m_string) == 0;
}

//Yaaay more operator overloading
bool FString::operator!=(const FString & f) const {
    return !(strcmp(m_string, f.m_string) == 0);
}

//Yaaaaay operator overloading make it stop :(
std::ostream & operator<<(std::ostream & os, const FString & f) {
    for(char *c = f.m_string; *c != '\0'; c++) 
	os << *c;
    return os;
}

std::istream & operator>>(std::istream & is, FString & f) {
    f.clear();

    char c = '\0';
    while((is.get(c)) != NULL) {
	f.concat(c);

	if(c == '\n' || c == '\0') {
	    break;
	}
    }
    return is;
}

//This function may or may not leak like a sieve
Linkedlist<FString *> FString::tokenize() const {
    
    Linkedlist<FString *> tokens;

    char *line = new char[ strlen(m_string)];
    char *line_iter = line;
    strcpy(line, m_string);

    int length = strlen(line);
    bool last_whitespace = true;

    char *substr_offset = NULL;
    int substr_length = 0;

    //Iterate over string and copy out words
    for(int i = 0; i < length; i++, line_iter++) {

	if(isspace(*line_iter)) { //Current position is boring
	    
	    if(!last_whitespace) { //Reached end of token
		FString *current_token = new FString(substr_offset, substr_length);
		tokens.add(current_token);

		substr_offset = NULL;
		substr_length = 0;
	    }
	    last_whitespace = true;
	}
	else {
	    if(last_whitespace) {
		last_whitespace = false;
		substr_offset = line_iter;
		substr_length = 1;
	    } 
	    else {
		substr_length++;
	    }

	}
    }

    if(substr_offset != NULL) { //Store remaining tokens
	FString *current_token = new FString(substr_offset, substr_length);
	tokens.add(current_token);
    }

    delete [] line;

    return tokens;
}

//Return token at set position
FString *FString::token(int i) const {
    
    Linkedlist<FString *> tokens = tokenize();

    if(tokens.size() >= i) {
	return tokens.get(i);
    }
    else {
	return NULL;
    }
}

//Return number of tokens that can be returned
int FString::count_tokens() const {
    return tokenize().size();
}

FString & FString::concat(const FString & f) {
    
    m_length += f.m_length;

    char *new_m_string = new char[ m_length + 1 ];

    strcpy(new_m_string, m_string);
    strcat(new_m_string, f.m_string);
    *(m_string + m_length) = '\0';

    delete [] m_string; //Deallocate current string

    m_string = new_m_string;

    return *this;
}

FString & FString::concat(const char *c_string) {
    return concat(FString(c_string));
}

FString & FString::concat(const char c) {

    //Allocate enough space for new char and null character
    m_length++;
    char *new_m_string = new char[ m_length + 2 ];
    memset(new_m_string, 0, m_length + 2);

    strcpy(new_m_string, m_string);
    
    *(new_m_string + strlen(m_string)) = c;
    *(new_m_string + strlen(m_string) + 1) = '\0';

    delete[] m_string;
    m_string = new_m_string;
    
    return *this;
}

void FString::clear() {
    delete [] m_string;
    m_string = new char[1];
    *m_string = '\0';

    m_length = 0;
}

