/* log.cc | A simple logging library for C++
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

std::string levels[6] = {"TRACE", "DEBUG", "INFO", "WARNING","ERROR", "FATAL"};
std::string level_colors[6] = {"\x1b[94m", "\x1b[36m", "\x1b[32m", "\x1b[33m", "\x1b[31m", "\x1b[35m"};

void logger::log(int level, const char *message, bool prompt)
{
	assert(level <= 5);
	time_t time_now = time(0);
	char *formated_time = ctime(&time_now);
	std::string level_text = levels[level];
	std::string level_color = level_colors[level];

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
	std::ofstream log_output;
	log_output.open(log_file, std::ios::app);
	std::clog << level_color	<< (prompt ? level_text : "")		<< NORMAL	<< TAB
		  << BOLD		<< (prompt ? formated_time : "")    	<< NORMAL	<< TAB
		  << message									<< std::endl;

	std::clog << std::endl;

	log_output << (prompt ? level_text : "")	<< TAB
		   << (prompt ? formated_time : "")	<< TAB
		   << message				<< std::endl;
	log_output << std::endl;

	// Unlock.
	lock = false;
	}
}

void logger::log(int level, int message, bool prompt)
{
	assert(level <= 5);
	time_t time_now = time(0);
	char *formated_time = ctime(&time_now);
	std::string level_text = levels[level];
	std::string level_color = level_colors[level];

	while(lock) {}

	if (level >= log_level && enabled) {
	lock = true;
	std::ofstream log_output;
	log_output.open(log_file,std::ios::app);

	std::clog << level_color	<< (prompt ? level_text : "")   	<< NORMAL	<< TAB
		  << BOLD 		<< (prompt ? formated_time : "")	<< NORMAL	<< TAB
		  << message									<< std::endl;
	std::clog << std::endl;

	log_output << (prompt ? level_text : "")	<< TAB
		   << (prompt ? formated_time : "")	<< TAB
		   << message				<< std::endl;
	log_output << std::endl;

	lock = false;
	}
}

void logger::log(int level, double message, bool prompt)
{
	assert(level <= 5);
	time_t time_now = time(0);
	char *formated_time = ctime(&time_now);
	std::string level_text = levels[level];
	std::string level_color = level_colors[level];

	while(lock) {}

	if (level >= log_level && enabled) {
        	lock = true;
        	std::ofstream log_output;
        	log_output.open(log_file,std::ios::app);
        	std::clog	<< level_color	<< (prompt ? level_text : "")		<< NORMAL	<< TAB
				<< BOLD		<< (prompt ? formated_time : "")	<< NORMAL	<< TAB;

        	printf("%lf\n", message);
        	std::clog << std::endl;

        	log_output	<< (prompt ? level_text : "")		<< TAB
                   		<< (prompt ? formated_time : "")	<< TAB
                   		<< message                       	<< std::endl;
        	log_output << std::endl;

        	lock = false;
    	}
}

void logger::set_log_level(int level)
{
    log_level = level;
}

void logger::disable()
{
	enabled = false;
}

void logger::enable()
{
	enabled = true;
}

int logger::get_log_level()
{
	return log_level;
}
