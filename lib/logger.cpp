/*
 * Implementation for singleton logger
 */

#include "../include/logger.h"

//Instantiate static variables
Logger *Logger::m_logger_instance = NULL;
unsigned short int Logger::m_level = 6;
const char *Logger::m_levels[7] = { "PANIC", "FATAL", "ERROR", "WARNING", "NOTICE", "INFO", "DEBUG" };
std::ostream *Logger::m_log_ostream = &std::cout;

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
	    *m_log_ostream << "DEBUG" << level - 5;
	}
	else {
	    *m_log_ostream << m_levels[level];
	}
	*m_log_ostream << ": " << message << std::endl;
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

void Logger::ostream(std::ostream *new_log_ostream) {
    m_log_ostream = new_log_ostream;
}

