#include "log.h"

/*
 * This is the example program.
 */

int main()
{
	logger l("log.txt");
	
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

    l.log(WARNING, 1);

	return 0;
}
