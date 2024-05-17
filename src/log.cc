#include "log.h"

string levels[6] = {"TRACE", "DEBUG", "INFO", "WARNINNG","ERROR", "FATAL"};
string level_colors[6] = {"\x1b[94m", "\x1b[36m", "\x1b[32m", "\x1b[33m", "\x1b[31m", "\x1b[35m"};

void logger::log(int level, const char *message)
{
	assert(level <= 5);
	time_t time_now = time(0);
	char *formated_time = ctime(&time_now);
	string level_text = levels[level];
	string level_color = level_colors[level];

    if (level >= log_level) {
        ofstream log(log_file);

        clog << level_color << level_text << NORMAL		<< TAB
             << BOLD << formated_time << NORMAL		<< TAB
             << message					<< endl;
        
        log << level 		<< TAB
            << formated_time 	<< TAB
            << message 		<< endl;
    }
}

void logger::set_log_level(int level)
{
    log_level = level;
}
