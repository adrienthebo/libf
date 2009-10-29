/*
 * Definition for a singleton logger class.
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>

class Logger {
    public:
    //Typedefs
	typedef short unsigned int loglevel_t;

    //Operations
	//Generate log message
	void log(loglevel_t level, const char *message);
	//Set current logging level
	loglevel_t & level();
	//Retrieve singleton instance
	static Logger *inst();
	//Set ostream
	void ostream(std::ostream *new_log_ostream);

	//Destructors
	~Logger();

    private:

    //Constructors
	Logger();

    //Members
	static Logger *m_logger_instance;
	static loglevel_t m_level;
	static const char *m_levels[];
	static std::ostream *m_log_ostream;
};

#endif
