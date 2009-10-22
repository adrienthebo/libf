/*
 * Definition for a singleton logger class.
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>

class Logger {
    public:
	typedef short unsigned int loglevel_t;

	void log(loglevel_t level, const char *message);
	loglevel_t & level();
	static Logger *inst();

	~Logger();
    private:
	Logger();
	static Logger *m_logger_instance;
	static loglevel_t m_level;
	static const char *m_levels[];

};

#endif
