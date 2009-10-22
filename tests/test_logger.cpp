/*
 * Tests for Logger
 */

#define BOOST_TEST_MODULE "logger main test suite"
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../include/logger.h"
#include <sstream>
#include <string>

BOOST_AUTO_TEST_CASE( test_log) {
    std::cout << "Testing logging facilities." << std::endl;
    
    std::stringstream str_stream;

    Logger::inst()->level() = 10;
    Logger::inst()->ostream(&str_stream);

    Logger::inst()->log(0, "PANIC MESSAGE");
    BOOST_CHECK(str_stream.str().compare("PANIC: PANIC MESSAGE"));

    Logger::inst()->log(1, "Fatal error message");
    BOOST_CHECK(str_stream.str().compare("FATAL: Fatal error message"));

    Logger::inst()->log(2, "Error message");
    BOOST_CHECK(str_stream.str().compare("ERROR: Error message"));
    
    Logger::inst()->log(3, "Warning message");
    BOOST_CHECK(str_stream.str().compare("WARNING: Warning message"));
    
    Logger::inst()->log(4, "Notice message");
    BOOST_CHECK(str_stream.str().compare("NOTICE: Notice message"));
    
    Logger::inst()->log(5, "Info message");
    BOOST_CHECK(str_stream.str().compare("INFO: Info message"));
    
    Logger::inst()->log(6, "Debug message");
    BOOST_CHECK(str_stream.str().compare("DEBUG: Debug message"));
    
    Logger::inst()->log(7, "Debug2 message");
    BOOST_CHECK(str_stream.str().compare("DEBUG2: Debug2 message"));
    
    Logger::inst()->log(8, "Debug3 message");
    BOOST_CHECK(str_stream.str().compare("DEBUG3: Debug3 message"));
    
    Logger::inst()->log(9, "Debug4 message");
    BOOST_CHECK(str_stream.str().compare("DEBUG4: Debug4 message"));
    
    Logger::inst()->log(10, "Debug5 message");
    BOOST_CHECK(str_stream.str().compare("DEBUG5: Debug5 message"));
    
    Logger::inst()->log(11, "Debug6 message, should not be viewed");
    BOOST_CHECK(str_stream.str().compare("DEBUG5: Debug5 message"));

    Logger::inst()->level() = 5;

    Logger::inst()->log(4, "Notice message");
    BOOST_CHECK(str_stream.str().compare("NOTICE: Notice message"));
    
    Logger::inst()->log(5, "Info message");
    BOOST_CHECK(str_stream.str().compare("INFO: Info message"));
    
    Logger::inst()->log(6, "Debug message, should not be viewed");
    BOOST_CHECK(str_stream.str().compare("INFO: Info message"));
}

