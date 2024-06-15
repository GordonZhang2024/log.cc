# log.cc
A simple logging library for C++
## This is a mirror from [log.cc on GitHub](https://github.com/GordonZhang2024/log.cc)
*This may not be up-to-date. To get the lastest version, please go to GitHub.*

## Usage
copy `src/log.cc` and `src/log.h` to your source directory.
### example
```cpp
#include "log.h"

int main()
{
	logger l("log.txt");
	l.log(ERROR, "error message");
	return 0;
}


```
###### Availible levels
> - TRACE
> - DEBUG
> - INFO
> - WARNING
> - ERROR
> - FATAL

**The full example is in the `example/` directory.**

#### Want to format the output?
You can use function `sprintf()` in `<cstdio>`.

#### Setting the log level
You can use the `set_log_level` function.
example: `l.set_log_level(WARNING);`

#### Disable
You can use the `disable` function.
example: `l.disable();`
To enable the logger again, use the `enable` function.
