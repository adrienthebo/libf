/*
 * Implementation for singleton logger
 */

#include "../include/logger.h"

//Instantiate static variables
Logger *Logger::m_logger_instance = NULL;
unsigned short int Logger::m_level = 6;
const char *Logger::m_levels[7] = { "PANIC", "FATAL", "ERROR", "WARNING", "NOTICE", "INFO", "DEBUG" };

Logger::Logger() { 
}

Logger::~Logger() { 
    if(m_logger_instance != NULL) {
	delete m_logger_instance;
    }
}

void Logger::log(unsigned short int level, const char *message) {
    if(level <= m_level) {
	if(level >= 7) {
	    std::cout << "DEBUG" << level - 5;
	}
	else {
	    std::cout << m_levels[level];
	}
	std::cout << ": " << message << std::endl;
    }
}

Logger *Logger::inst() {
    if(m_logger_instance == NULL) {
	m_logger_instance = new Logger();
    }

    return m_logger_instance;
}

unsigned short int & Logger::level() {
    return m_level;
}

