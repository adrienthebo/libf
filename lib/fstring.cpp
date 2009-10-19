
#include "../include/fstring.h"
#include <cstring>

FString::FString() {
    m_string = new char[1];
    strcpy(m_string, "\0");
}

FString::FString(const char *c_string) {
    m_string = new char[strlen(c_string)];
    strcpy(m_string, c_string);
}

FString::FString(const FString & f) {
    m_string = new char[strlen(f.m_string)];
    strcpy(m_string, f.m_string);
}

FString::FString(const char *c_string, unsigned int length) {
    m_string = new char[length + 1];
    strncpy(m_string, c_string, length);
    *(m_string + length + 1) = '\0';
    //TODO remove
    //std::cout << "\nHOLY SHIT STRING: \"" << *this << "\"" << std::endl;
}

FString::~FString() {
    //TODO remove
    //std::cout << "Stomping on " << m_string << " with address of " << this << std::endl;
    delete [] m_string;
}

int FString::size() {
    return (m_string == NULL) ? 0 : strlen(m_string);
}

char *FString::cstring() {
    char *c_string = new char[ strlen(m_string)];

    strcpy(c_string, m_string);

    return c_string;
}

bool FString::operator==(FString & f) {
    return strcmp(m_string, f.m_string) == 0;
}

bool FString::operator!=(FString & f) {
    return !(strcmp(m_string, f.m_string) == 0);
}

std::ostream & operator<<(std::ostream & os, const FString s) {
    for(char *c = s.m_string; *c != '\0'; c++) 
	os << *c;
    return os;
}

/* This is going to leak like a sieve */
Linkedlist<FString *> FString::tokenize() {
    
    Linkedlist<FString *> tokens;

    char *line = new char[ strlen(m_string) + 1];
    char *line_iter = line;
    strcpy(line, m_string);

    //std::cout << "Line: " << FString(line) << std::endl;

    int length = strlen(line);
    bool last_whitespace = true;

    char *substr_offset = NULL;
    int substr_length = 0;


    for(int i = 0; i < length; i++, line_iter++) {
	//std::cout << *line_iter;

	if(isspace(*line_iter)) {
	    
	    if(!last_whitespace) { //Reached end of token
		FString *current_token = new FString(substr_offset, substr_length);
		//TODO remove
		//std::cout << *current_token << std::endl;
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
	//TODO removeme
	//std::cout << *current_token << std::endl;
    }

    delete [] line;

    return tokens;
}

FString *FString::token(int i) {
    
    Linkedlist<FString *> tokens = tokenize();

    if(tokens.size() >= i) {
	return tokens.get(i);
    }
    else {
	return NULL;
    }
}

int FString::count_tokens() {
    return tokenize().size();
}
