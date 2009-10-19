# flib Makefile

CC = g++
AR = ar

CXXFLAGS = -Iinclude -Wall -g
ARFLAGS = rv

VPATH = lib include tests

.PHONY: all check clean
all: fstring.a

test_fstring.o: test_fstring.cpp
fstring.o: fstring.cpp fstring.h

test_fstring: fstring.o test_fstring.o
	$(CC) $(LDFLAGS) -o $@ $^ 
test_liblinkedlist: test_linkedlist.cpp
	$(CC) $(LDFLAGS) -lboost_unit_test_framework -o $@ $^

fstring.a: fstring.o
	$(AR) $(ARFLAGS) $@ $^

# This is pretty much worthless
liblinkedlist.a: liblinkedlist.h node.h listexception.h 
	$(AR) $(ARFLAGS) $@ $^

check: test_fstring test_liblinkedlist
	./test_fstring
	./test_liblinkedlist

clean:
	rm -f test_main.o \
	    test_fstring.o \
	    fstring.o \
	    testapp \
	    fstring.a;
	rm -f test_linkedlist.o \
	    listexception.o \
	    testapp \
	    liblinkedlist.a;

