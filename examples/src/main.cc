#include "log.h"

int main()
{
	logger l("log.txt");
	l.log(ERROR, "error");
	return 0;
}
