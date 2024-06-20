/*
 * log.cc | A simple logging library for C++
 * ========================================
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
#include <iostream>

/*
 * This is the example program.
 */

int main()
{
	logger l("log.txt");

	// Clear the existing log file.
	l.clear_log();

	std::cout << "This is the example program for log.cc." << std::endl;
	std::cout << std::endl;
	
	l.log(ERROR, "error message");
	l.log(DEBUG, "debug message");
	
	// Disable the logger
	l.disable();
	l.log(DEBUG, "This message will never be shown."); // This message will never be shown.
	
	// Enable the logger again
	l.enable();
	// Set the log level to warning.
	// Now only the messages whose level >= WARNING can be shown.
	l.set_log_level(WARNING);
	l.log(INFO, "This message will never be shown."); // This message will never be shown because Its level is too low.
	l.log(WARNING, "%d", 1); // you can use an integer or double as the message.
	l.log(WARNING, "%d", 1.1);
	std::cout << ">> TIPS You can use an integer or double(float) as the log message." << std::endl;
	std::cout << std::endl;

	l.set_log_level(DEBUG);

	// You can't see the prompt(time, log level) in this log message.
	l.log(INFO, "This message contains no prompt", false);

	return 0;
}
