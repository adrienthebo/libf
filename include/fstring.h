#ifndef FSTRING_H
#define FSTRING_H

#include <iostream>
#include "liblinkedlist.h"

class FString {
    private:
	char *m_string;
    public:
	FString();
	FString(const FString & f);
	FString(const char *c_string);
	FString(const char *c_string, unsigned int length);

	~FString();
	
	char *cstring();
	int size();
	Linkedlist<FString *> tokenize();
	FString *token(int i);
	int count_tokens();

	bool operator==(FString & f);
	bool operator!=(FString & f);

	friend std::ostream & operator<<(std::ostream & os, const FString s);
};

#endif
