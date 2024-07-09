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

*The following examples uses `l` as the default logger name.*

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

#### Disable the terminal output
Sometimes, it's necessary to disable the terminal log output (especially when developing a GUI app, users don't want to see a terminal with plenty of messages).

```cpp
l.disable_terminal_output();
```

To enable terminal output again, use the `enable_terminal_output` function.

#### More info

You can view `log.cc` and `log.h` in the `src` dir.

## License

[MIT License](https://github.com/GordonZhang2024/log.cc/blob/main/LICENSE)
