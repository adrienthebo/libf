# flib Makefile

CC = g++
AR = ar

CXXFLAGS = -Iinclude -Wall -g -pipe
ARFLAGS = rv
BOOST_LDFLAGS = -lboost_unit_test_framework

VPATH = lib include tests

.PHONY: all check clean
all: flib.a

logger.o: logger.cpp logger.h
fstring.o: fstring.cpp fstring.h

test_fstring.o: test_fstring.cpp
test_logger.o: test_logger.cpp
test_linkedlist.o: test_linkedlist.cpp
test_bst.o: test_bst.cpp

test_bst: test_bst.o
	$(CC) $(LDFLAGS) $(BOOST_LDFLAGS) -o $@ $^
test_fstring: fstring.o test_fstring.o
	$(CC) $(LDFLAGS) $(BOOST_LDFLAGS) -o $@ $^ 
test_liblinkedlist: test_linkedlist.o
	$(CC) $(LDFLAGS) $(BOOST_LDFLAGS) -o $@ $^
test_logger: logger.o test_logger.o
	$(CC) $(LDFLAGS) $(BOOST_LDFLAGS) -o $@ $^


flib.a: fstring.o logger.o
	$(AR) $(ARFLAGS) $@ $^

# This is pretty much worthless
liblinkedlist.a: liblinkedlist.h node.h listexception.h 
	$(AR) $(ARFLAGS) $@ $^

check: test_fstring test_liblinkedlist test_bst test_logger
	./test_fstring
	./test_liblinkedlist
	./test_bst
	./test_logger

clean:
	rm -f fstring.o \
	    logger.o;
	rm -f \
	    test_fstring \
	    test_liblinkedlist \
	    test_bst \
	    test_logger ;
	rm -f flib.a;
	rm -f \
	    test_fstring.o \
	    test_logger.o \
	    test_linkedlist.o \
	    test_bst.o ;
