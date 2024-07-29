/* ===============================================================================
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
#include <iostream> // In fact, this line is unnecessary because <iostream> is already included in "log.h"
#include <cstdlib>

using std::cout;
using std::endl;

/*
 * This is the example program.
 * You can learn how to use log.cc from it.
 */

int main()
{
	logger l("log.txt");

	l.addLogFile("another-log.txt"); // Add another log file

	// Clear the existing log file.
	l.clearLog();

	cout << endl;
	cout << "========== This is the example program for log.cc. =======================" << endl;
	cout << endl;

	// Some example messges.
	l.log(TRACE, "Trace message"); 	
	l.log(DEBUG, "Debug message");
	l.log(INFO, "Info message");
	l.log(WARNING , "Warning message");
	l.log(ERROR, "Error message");
	l.log(FATAL, "Fatal message");

	cout << endl;

	l.disable();
	/*
	 * Now the logger is disabed.
	 * All the log messages will be ignored
	 */
	l.log(DEBUG, "This message will never be shown."); // This message will never be shown.
	
	// Enable the logger again
	l.enable();

	/*
	 * Set the log level to warning.
	 *Now only the messages that are more important than WARNING (or as important as WARNING) can be shown.
	 */
	l.setLogLevel(WARNING);

	auto current_level = l.getLogLevel();

	l.log(WARNING, "Current log level: %d", current_level);

	// This message will never been shown because its level is too low.
	l.log(INFO, "This message will never be shown.");
	cout << endl;

	l.log(WARNING, "A number: %d", 1); // you can use an integer or double as the message.
	l.log(WARNING, "A float: %f", 1.1);
	cout << ">> You can use an integer or double (float) as the log message." << endl;
	cout << endl;

	l.setLogLevel(DEBUG);
	
	l.disableTerminalOutput();
	/*
	 * Now the terminal output is disabled.
	 * The log will only be written to the log file.
	 */
	l.log(INFO, "This message is only shown in the log file.");
	l.enableTerminalOutput(); //Enable the terminal output again.

	cout	<< "Now you can take a look at the files in this directory."	<< endl
			<< "You can find log.txt and another-log.txt."			<< endl
			<< "They are all created by this program."			<< endl
			<< "You can also find an extra log message which is not shown in the terminal."
			<< endl;

	/*
	 * That's all. I hope you will like this logging library.
	 * :)
	 */

	cout << endl;
	cout << "==========================================================================" << endl;
	cout << endl;

	return EXIT_SUCCESS;
}

