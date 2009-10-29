#ifndef FSTRING_H
#define FSTRING_H

#include <iostream>
#include <cstring>
#include "linkedlist.h"

class FString {
    private:
	char *m_string;
	unsigned int m_length;
    public:
	//Constructors
	FString();
	FString(const FString & f);
	FString(const char *c_string); FString(const char *c_string, const unsigned int length);

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
	FString & concat(const char *c_string);
	FString & concat(const char c);

	//Overloaded operators
	bool operator==(const FString & f) const;
	bool operator!=(const FString & f) const;
	friend std::ostream & operator<<(std::ostream & os, const FString & f);
	friend std::istream & operator>>(std::istream & is, FString & f);
	
	//Misc
	void clear();
};

#endif
