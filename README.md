# Log.cc

A simple logging library for C++

## Usage

Copy `src/log.cc` and `src/log.h` to your source directory.

### Example

```cpp
#include "log.h"

int main()
{
    logger l("log.txt");
    l.log(ERROR, "error message");
    return 0;
}


```

#### Available levels

> - TRACE
> - DEBUG
> - INFO
> - WARNING
> - ERROR
> - FATAL

**The full example is in the `example/` directory. You can find more useful functions from log.cc**

#### Want to format the output?

You can use the `log()` function in this way, just like `printf()`:

```cpp
l.log(WARNING, "%d", 1);
```

#### Setting the log level

You can use the `set_log_level` function.
Example: `l.set_log_level(WARNING);`

#### Disable

You can use the `disable` function.
Example: `l.disable();`
To enable the logger again, use the `enable` function.

## License

MIT License

