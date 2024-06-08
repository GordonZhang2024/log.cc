#ifndef LOG_H
#define LOG_H
#include <iostream>
#include <fstream>
#include <ctime>
#include <cassert>
#include <initializer_list>

#define TRACE 		0
#define DEBUG 		1
#define INFO 		2
#define WARNING 	3
#define ERROR 		4
#define FATAL 		5

#define TAB 		"\t"
#define NORMAL      "\x1b[0m"
#define BOLD        "\x1b[1m"

class logger {
	public:
		logger(const char *filename)
		{
			log_file = filename;
		}

		const char *log_file;
		void log(int level, const char *text, bool prompt=true);
		void log(int level, int text, bool prompt=true);
		void log(int level, double text, bool prompt=true);
		void set_log_file(std::ofstream &file);
		void set_log_level(int level);
		void disable();
		void enable();
		int get_log_level();
		

	private:
		int log_level = 0;
		bool enabled = true;

};
#endif
