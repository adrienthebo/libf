# flib Makefile

CC = g++
AR = ar

CXXFLAGS = -Iinclude -Wall -g -pipe
ARFLAGS = rv
BOOST_LDFLAGS = -lboost_unit_test_framework

VPATH = lib include tests

.PHONY: all tests check clean

all: libf.a

# Library archive
libf.a: fstring.o logger.o
	$(AR) $(ARFLAGS) $@ $^

# Library implementations
logger.o: logger.cpp logger.h
fstring.o: fstring.cpp fstring.h

# Test applications
test_fstring.o: test_fstring.cpp
test_logger.o: test_logger.cpp
test_linkedlist.o: test_linkedlist.cpp
test_bst.o: test_bst.cpp

# Test binaries
test_bst: test_bst.o
	$(CC) $(LDFLAGS) $(BOOST_LDFLAGS) -o $@ $^
test_fstring: fstring.o test_fstring.o
	$(CC) $(LDFLAGS) $(BOOST_LDFLAGS) -o $@ $^ 
test_linkedlist: test_linkedlist.o
	$(CC) $(LDFLAGS) $(BOOST_LDFLAGS) -o $@ $^
test_logger: logger.o test_logger.o
	$(CC) $(LDFLAGS) $(BOOST_LDFLAGS) -o $@ $^


# compiling and running all tests
tests: test_fstring test_linkedlist test_bst test_logger

check: tests
	./test_linkedlist
	./test_bst
	./test_fstring
	./test_logger

# HI, BILLY MAYS HERE WITH OXY CLEAN
clean:
	rm -f fstring.o \
	    logger.o;
	rm -f \
	    test_fstring \
	    test_linkedlist \
	    test_bst \
	    test_logger ;
	rm -f libf.a;
	rm -f \
	    test_fstring.o \
	    test_logger.o \
	    test_linkedlist.o \
	    test_bst.o ;
