# Log.cc

A simple logging library for C++

![GitHub License](https://img.shields.io/github/license/GordonZhang2024/log.cc)
![Static Badge](https://img.shields.io/badge/love-love?label=%E2%9D%A4%EF%B8%8FMade%20with&labelColor=black&color=red)


## Usage
> Log.cc is very easy to use.
>
> To use log.cc for your own project, you only need to copy `src/log.cc` and `src/log.h` to your own source directory.

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

> [!NOTE]
> #### Available levels
> 
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
> [!TIP]
> ### More info
> **There are also many useful functions in *log.cc***.
> **You can view the [Wiki page](https://github.com/GordonZhang2024/log.cc/wiki/Log.cc-usage) for more info.**


## License

[MIT License](https://github.com/GordonZhang2024/log.cc/blob/main/LICENSE)
