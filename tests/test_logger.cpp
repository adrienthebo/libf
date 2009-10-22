/*
 * Tests for Logger
 */

#include "../include/logger.h"

int main(int argc, char **argv) {
    
    Logger::inst()->level() = 10;
    Logger::inst()->log(0, "PANIC MESSAGE");
    Logger::inst()->log(1, "Fatal error message");
    Logger::inst()->log(2, "Error message");
    Logger::inst()->log(3, "Warning message");
    Logger::inst()->log(4, "Notice message");
    Logger::inst()->log(5, "Info message");
    Logger::inst()->log(6, "Debug message");
    Logger::inst()->log(7, "Debug2 message");
    Logger::inst()->log(8, "Debug3 message");
    Logger::inst()->log(9, "Debug4 message");
    Logger::inst()->log(10, "Debug5 message");
    Logger::inst()->log(11, "Debug6 message, should not be viewed");
    return 0;
}

