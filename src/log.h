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
 */

#ifndef LOG_H_
#define LOG_H_

#include <iostream>
#include <cstdio>
#include <fstream>
#include <ctime>
#include <cassert>
#include <cstdarg>
#include <vector>

// Availible log levels
#define TRACE 		0
#define DEBUG 		1
#define INFO 		2
#define WARNING 	3
#define ERROR 		4
#define FATAL 		5

#define TAB		"\t"
#define NORMAL		"\x1b[0m"
#define BOLD		"\x1b[1m"


char generateFilename(const char *name="log");


class logger {
	public:
		logger(const char *filename)
		{
			logFiles.push_back(filename);
			lock = false;
			enabled = true;
			terminalOutputEnabled = true;
		}

		logger()
		{
			lock = false;
			enabled = true;
		}

		std::vector<const char*>	logFiles;
		void				log(int level, const char   *message, ...);
		void				clearLog();
		void				clearLog(int index);
		void				setLogFile(std::ofstream &file);
		void				setLogLevel(int level);
		void				disable();
		void				enable();
		int				getLogLevel();
		void				addLogFile(const char *filename);
		void				disableTerminalOutput();
		void				enableTerminalOutput();

	private:
		int				logLevel = 0;
		bool				lock;
		bool				enabled;
		bool				terminalOutputEnabled;
};
#endif // LOG_H_
