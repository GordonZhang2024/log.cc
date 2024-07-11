# Log.cc

A simple logging library for C++

## Usage
Log.cc is very easy to use.


You only need  to copy `src/log.cc` and `src/log.h` to your own source directory.

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

**The full example is in the `example/` directory. You can find more useful functions from `log.cc`**

*The following examples use `l` as the default logger name.*

### Want to format the output?

You can use the `log()` function in this way, just like `printf()`:

```cpp
l.log(WARNING, "%d", 1);
```

### More info
You can view the [Wiki page](https://github.com/GordonZhang2024/log.cc/wiki/Log.cc-usage)


## License

[MIT License](https://github.com/GordonZhang2024/log.cc/blob/main/LICENSE)
