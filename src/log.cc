/* ===============================================================================
 * log.cc | A light-weight and easy-to-use logging library for C++
 * ===============================================================================
 * License : MIT License
 *
 * Copyright (c) 2024 Gordon Zhang
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * ===============================================================================
 */

#include "log.h"

// Availible log levels and colors for them.
std::string levels[6]		= {
	"TRACE",    "DEBUG",    "INFO",
	"WARNING",  "ERROR",    "FATAL"
};
std::string levelColors[6]	= {
	"\x1b[94m", "\x1b[36m", "\x1b[32m",
	"\x1b[33m", "\x1b[31m", "\x1b[35m"
};


void logger::log(int level, const char *format, ...)
{
	/*
	 * This is the master logging function.
	 */

	/*
	 * Get the arguments.
	 */
	va_list args;
	va_start(args, format);

	assert(level <= 5);  // The log level shouldn't be >= 5.

	// Get the time and format it.
	time_t timeNow = time(0);
	char *formattedTime = ctime(&timeNow);

	// Get the log level std::string and log level color.
	std::string levelText = levels[level];
	std::string levelColor = levelColors[level];


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
	// Do terminal output if it is enabled.
	if (level >= logLevel && enabled) {
		lock = true;
		if (terminalOutputEnabled) {
			std::clog << levelColor		<< levelText		<< NORMAL	<< TAB
				  << BOLD		<< formattedTime    	<< NORMAL	<< TAB
				  <<message							<< std::endl;

			std::clog << std::endl;
		}

		for (int file = 0; file < logFiles.size(); ++file) {
			std::ofstream log_output;
			const char *current_file = logFiles[file];
			log_output.open(current_file, std::ios::app);
			lock = true;
			log_output << levelText	<< TAB
				   << formattedTime	<< TAB
				   << message		<< std::endl;
			log_output << std::endl;

			// Unlock.
			lock = false;
		}
	}

	va_end(args);
}


void logger::setLogLevel(int level)
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

	assert(level <= 5); // The log level shouldn't be >= 5.
	logLevel = level;
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
	 *
	 * > The logger is enabled when it is created.
	 * > You only need to use it when the logger is disabled by you
	 * > with the disable() function.
	 *
	 */

	enabled = true;
}


int logger::getLogLevel()
{
	/* Get the log level
	 *
	 * Return value
	 * ============
	 * Integer, the log level of the current logger.
	 */
	return logLevel;
}


void logger::clearLog()
{
	// Clear all existing log files.
	for (int file = 0; file < logFiles.size(); ++file) {
		std::ofstream fout(logFiles[file]);
		fout << "";
	}
}


void logger::clearLog(int index)
{
	/*
	 * Clear a spectific log file.
	 * index should be the index of the log file,
	 * for example, index=0 means the first log file.
	 */

	std::ofstream fout(logFiles[index]);
	fout << "";
}


void logger::addLogFile(const char *log_file)
{
	/*
	 * Add a log file.
	 * The log message will me written to all the log files.
	 */
	logFiles.push_back(log_file);
}


void logger::disableTerminalOutput()
{
	/*
	 * The log message will not be shown oon the terminal
	 * if the terminal_output is disabled.
	 */
	terminalOutputEnabled = false;
}


void logger::enableTerminalOutput()
{
	// Enable the terminal output again.
	terminalOutputEnabled = true;
}


std::string replaceSpaces(char *text)
{
	/*
	 * This function is used to format the time for the filename generator.
	 */

	std::string sText = text;
	
	for (	std::string::iterator iter = sText.begin();
		iter < sText.end();
		++iter
	) {
		char currentChar = *iter;
		if (currentChar == ' ')
			*iter = '_';
	}

	sText.pop_back();  // Remove the "\n" at the end.

	return sText;
}



std::string generateFilename(std::string name, std::string filenameExtension)
{
	/*
	 * Generate a file name.
	 *
	 * Arguments
	 * =========
	 * - name:
	 *   > The name of your application, "log" by default
	 * - filenameExtension:
	 *   > The filename extension for your log file, "txt" by default.
	 *   > Note that you don't have to include a dot in it.
	 *   > Filename extensions do not matter for Unix-like Operating Systems.
	 *   > However, it will be greate to customize your own filename extension, 
	 *   > you may want something like ".log" instead of ".txt".
	 *
	 */

	// Get the time and format it.
	time_t timeNow = time(0);
	char *cTime = ctime(&timeNow);
	std::string formattedTime = replaceSpaces(cTime);

	std::string filename;

	filename = name + "-" + formattedTime + "." + filenameExtension;

	return filename;
}



int getLongest(table t)
{
	/*
	 * Get the length of the longest item in the table.
	 */

	int longest = 0;

	for (table::iterator iterOfRow = t.begin(); iterOfRow < t.end(); ++iterOfRow) {
		row currentRow = *iterOfRow;
		for (row::iterator iterOfItem = currentRow.begin(); iterOfItem < currentRow.end(); ++iterOfItem) {
			std::string currentItem = *iterOfItem;
			int lenOfItem = currentItem.size();

			if (lenOfItem >= longest)
				longest = lenOfItem;
		}
	}

	++longest;
	return longest;
}


int getLongestRow(table t)
{
	/*
	 * Get the length of the longest row in the table.
	 */

	int longest = 0;

	for (table::iterator iterOfRow = t.begin(); iterOfRow < t.end(); ++iterOfRow) {
		row currentRow = *iterOfRow;
		if (currentRow.size() >  longest)
			longest = currentRow.size();
	}

	++longest;

	int longestItem = getLongest(t);
	longest *= longestItem;

	return longest;
}


std::string formatItem(std::string &s, int len)
{
	/*
	 * Format an item to make it as long as any other item in the table.
	 */

	while (s.size() < len)
		s += " ";

	return s;
}


void split(int len)
{
	/*
	 * Split (Used for printing a table)
	 */

	std::cout << " +=";

	while (len > 0) {
		std::cout << "=";
		--len;
	}

	std::cout << "+" << std::endl;
}


void log(table t)
{
	/*
	 * Output a table.
	 *
	 * Arguments
	 * =========
	 * - table
	 *   > type: table, which is a vector<string>.
	 */

	int longest = getLongest(t);
	int longestRow = getLongestRow(t);

	split(longestRow);

	for (table::iterator iterOfRow = t.begin(); iterOfRow < t.end(); ++iterOfRow) {
		row currentRow = *iterOfRow;

		std::cout << " | ";

		for (row::iterator iterOfItem = currentRow.begin(); iterOfItem < currentRow.end(); ++iterOfItem) {
			std::string currentItem = *iterOfItem;

			formatItem(currentItem, longest);

			std::cout << currentItem << "|" << " ";
		}
		std::cout << std::endl;
		split(longestRow);
	}
}

