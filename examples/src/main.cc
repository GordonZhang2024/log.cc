#include "log.h"

int main()
{
	logger l("log.txt");
	l.log(ERROR, "error message");
	l.log(DEBUG, "debug message");
	
	l.disable();
	l.log(DEBUG, "This message will never be shown");
	
	l.enable();
	l.set_log_level(WARNING);
	l.log(INFO, "This message will never be shown");

	return 0;
}
