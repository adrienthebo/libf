#ifndef FSTRING_H
#define FSTRING_H

#include <iostream>
#include "liblinkedlist.h"

class FString {
    private:
	char *m_string;
    public:
	//Constructors
	FString();
	FString(const FString & f);
	FString(const char *c_string);
	FString(const char *c_string, const unsigned int length);

	~FString();
	
	//pseudo accessors
	char *cstring() const;
	int size() const;

	//tokenizers
	Linkedlist<FString *> tokenize() const;
	FString *token(int i) const;
	int count_tokens() const;

	//concatenation
	FString & concat(const FString & f);

	//Overloaded operators
	bool operator==(FString & f);
	bool operator!=(FString & f);
	friend std::ostream & operator<<(std::ostream & os, const FString s);
};

#endif
