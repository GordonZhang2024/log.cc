# log.cc
A simple logging library for C++
## Usage

copy `src/log.cc` and `src/log.h` to your source directory.
### example
```cpp

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
