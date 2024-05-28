#ifndef LOG_H
#define LOG_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cassert>

#define TRACE 		0 
#define DEBUG 		1
#define INFO 		2
#define WARNING 	3
#define ERROR 		4
#define FATAL 		5

#define TAB 		"\t"
#define NORMAL "\x1b[0m"
#define BOLD "\x1b[1m"

using std::ofstream;
using std::clog;
using std::cout;
using std::endl;
using std::vector;
using std::string;

class logger {
	public:
		logger(const char *filename)
		{
			log_file = filename;
		}
		const char *log_file;
		void log(int level, const char *text);
		void log(int level, int text);
		void log(int level, double text);
		void set_log_file(ofstream &file);
        void set_log_level(int level);
		void disable();
		void enable();
		int get_log_level();
	private:
        int log_level = 0;
		bool enabled = true;

};
#endif
