/* 
 * Defines a string class based off of a char array.
 */
#include "../include/fstring.h"
#include <cstring>

//Default constructor
FString::FString() {
    m_string = new char[1];
    strcpy(m_string, "\0");
}

//cstring constructor
FString::FString(const char *c_string) {
    m_string = new char[strlen(c_string)];
    strcpy(m_string, c_string);
}

//Copy constructor
FString::FString(const FString & f) {
    m_string = new char[strlen(f.m_string)];
    strcpy(m_string, f.m_string);
}

//Bounded cstring constructor (only copy (int)length elements)
FString::FString(const char *c_string, const unsigned int length) {
    m_string = new char[length + 1];
    strncpy(m_string, c_string, length);
    *(m_string + length) = '\0';
}

//Array destructor
FString::~FString() {
    delete [] m_string;
}  

//Null safe size
int FString::size() const {
    return strlen(m_string);
}

//Returns a cstring copy of the fstring
char *FString::cstring() const {
    char *c_string = new char[ strlen(m_string)];

    strcpy(c_string, m_string);

    return c_string;
}

//Yaaaay operator overloading
bool FString::operator==(FString & f) {
    return strcmp(m_string, f.m_string) == 0;
}

//Yaaay more operator overloading
bool FString::operator!=(FString & f) {
    return !(strcmp(m_string, f.m_string) == 0);
}

//Yaaaaay operator overloading make it stop :(
std::ostream & operator<<(std::ostream & os, const FString s) {
    for(char *c = s.m_string; *c != '\0'; c++) 
	os << *c;
    return os;
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
    
    char *new_m_string = new char[ strlen(m_string) + strlen(f.m_string) ];

    strcpy(new_m_string, m_string);
    strcat(new_m_string, f.m_string);

    delete [] m_string; //Deallocate current string

    m_string = new_m_string;

    return *this;
}

