/*
 * log.cc | A simple logging library for C++
 * =========================================
 * License : MIT License
 * Copyright (c) 2024 Gordon Zhang

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "log.h"

std::string levels[6]		= {"TRACE",		"DEBUG",	"INFO",		"WARNING",	"ERROR",	"FATAL"};
std::string level_colors[6]	= {"\x1b[94m",		"\x1b[36m",	"\x1b[32m",	"\x1b[33m",	"\x1b[31m",	"\x1b[35m"};

void logger::log(int level, const char *format, ...)
{
	va_list args;
	va_start(args, format);

	assert(level <= 5); // The log level shouldn't be >= 5.

	// Get the time.
	time_t time_now = time(0);
	char *formatted_time = ctime(&time_now);

	// Get the log level string and log level color.
	std::string level_text = levels[level];
	std::string level_color = level_colors[level];

	

	// Format the log message.
	char message[9999];
	vsprintf(message, format, args);


	/* If current message is important enough(current level > log level)
	* and the logger is enabled.
	* The logger shouln't be locked.
	* (
	*  when another process is creating a log message, the logger will
	*  be locked.
	* )
	* The lock is used to prevent multiple log messages written in the same time.
	*/

	// Wait until unlock.
	while (lock) {
	/* Do nothing. Just wait.*/
	}
	if (level >= log_level && enabled) {
		lock = true;
		std::clog << level_color	<< level_text		<< NORMAL	<< TAB
			  << BOLD		<< formatted_time    	<< NORMAL	<< TAB
			  <<message							<< std::endl;

		std::clog << std::endl;

		for (int i = 0; i < log_files.size(); ++i) {
			std::ofstream log_output;
			const char *current_file = log_files[i];
			log_output.open(current_file, std::ios::app);
			lock = true;
			log_output << level_text	<< TAB
				   << formatted_time	<< TAB
				   <<message		<< std::endl;
			log_output << std::endl;

			// Unlock.
			lock = false;
		}
	}

	va_end(args);
}


void logger::set_log_level(int level)
{
	/*
	 * Set the log level.
	 */

	/*
	 * What's the log level?
	 * =====================
	 *
	 * Log level is a part of a logger.
	 * A log message only appears when its level >= the logger's
	 * log level.
	 * 
	 * For example, you can set it as ERROR if you don't want to see too 
	 * much INFO message or DEBUG message.
	 */

	log_level = level;
}

void logger::disable()
{
	/*
	 * Disable the logger.
	 */

	/*
	 * You can use this function if you don't want to see any log message.
	 * You can always enable the logger again with function enable().
	 */

	enabled = false;
}

void logger::enable()
{
	/*
	 * This funciton it used to enable the logger again.
	 * (
	 * 	The logger is enabled when it is created.
	 * 	You only need to use it when the logger is disabled by you with the disable() function.
	 * )
	 */

	enabled = true;
}

int logger::get_log_level()
{
	return log_level;
}


void logger::clear_log()
{
	// Clear all log files.
	for (int i = 0; i < log_files.size(); ++i) {
		std::ofstream fout(log_files[i]);
		fout << "";
	}
}

void logger::clear_log(int index)
{
	/*
	 * Clear a spectific log file.
	 * index should be the index of the log file,
	 * for example, index=0 means the first log file.
	 */

	std::ofstream fout(log_files[index]);
	fout << "";
}


void logger::add_log_file(const char *log_file)
{
	log_files.push_back(log_file);
}
