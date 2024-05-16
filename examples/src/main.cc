#include "log.h"

int main()
{
	logger l("log.txt");
	l.log(ERROR, "error message");
	l.log(DEBUG, "debug message");
	return 0;
}
