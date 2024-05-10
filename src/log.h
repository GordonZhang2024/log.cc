#ifndef LOG_H
#define LOG_H
#include <iostream>
#include <vector>
#include <string>
#include <ctime>

#define TRACE "TRACE"
#define DEBUG "DEBUG"
#define INFO "INFO"
#define WARNING "WARNING"
#define ERROR "ERROR"
#define FATAL "FATAL"

#define TAB "\t"

using std::clog;
using std::cout;
using std::endl;
using std::vector;
using std::string;

class logger {
	private:
		vector<string> callback_files;
	public:
		void log(const char *level, const char *message);
		void add_callback_file(string file);
		void show_callback_files();
};
#endif
