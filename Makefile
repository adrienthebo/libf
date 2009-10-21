# flib Makefile

CC = g++
AR = ar

CXXFLAGS = -Iinclude -Wall -g
ARFLAGS = rv
BOOST_LDFLAGS = -lboost_unit_test_framework

VPATH = lib include tests

.PHONY: all check clean
all: fstring.a

test_fstring.o: test_fstring.cpp
fstring.o: fstring.cpp fstring.h
treeexception.o: treeexception.cpp treeexception.h

test_bst: test_bst.cpp
	$(CC) $(LDFLAGS) $(BOOST_LDFLAGS) -o $@ $^
test_fstring: fstring.o test_fstring.o
	$(CC) $(LDFLAGS) $(BOOST_LDFLAGS) -o $@ $^ 
test_liblinkedlist: test_linkedlist.cpp
	$(CC) $(LDFLAGS) $(BOOST_LDFLAGS) -o $@ $^

fstring.a: fstring.o
	$(AR) $(ARFLAGS) $@ $^

# This is pretty much worthless
liblinkedlist.a: liblinkedlist.h node.h listexception.h 
	$(AR) $(ARFLAGS) $@ $^

check: test_fstring test_liblinkedlist test_bst
	./test_fstring
	./test_liblinkedlist
	./test_bst

clean:
	rm -f fstring.o \
	    test_fstring.o \
	    fstring.a;
	rm -f test_fstring \
	test_liblinkedlist \
	test_bst;
