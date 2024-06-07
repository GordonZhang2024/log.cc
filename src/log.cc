#include "log.h"

std::string levels[6] = {"TRACE", "DEBUG", "INFO", "WARNING","ERROR", "FATAL"};
std::string level_colors[6] = {"\x1b[94m", "\x1b[36m", "\x1b[32m", "\x1b[33m", "\x1b[31m", "\x1b[35m"};

void logger::log(int level, const char *message)
{
	assert(level <= 5);
	time_t time_now = time(0);
	char *formated_time = ctime(&time_now);
	std::string level_text = levels[level];
	std::string level_color = level_colors[level];

    if (level >= log_level && enabled) {
        std::ofstream log_output(log_file);

        std::clog << level_color    <<level_text		<< NORMAL	<< TAB
                  << BOLD 		    << formated_time	<< NORMAL	<< TAB
                  << message							<< std::endl;
        
        log_output << level 		<< TAB
                   << formated_time	<< TAB
        	       << message 		<< std::endl;
    }
}

void logger::log(int level, int message)
{
	assert(level <= 5);
	time_t time_now = time(0);
	char *formated_time = ctime(&time_now);
	std::string level_text = levels[level];
	std::string level_color = level_colors[level];

    if (level >= log_level && enabled) {
        std::ofstream log_output(log_file);

        std::clog << level_color<< level_text		<< NORMAL	<< TAB
            	  << BOLD 		<< formated_time	<< NORMAL	<< TAB
            	  << message						<< std::endl;
        
        log_output << level		<< TAB
        	   << formated_time << TAB
        	   << message		<< std::endl;
    }
}

void logger::log(int level, double message)
{
	assert(level <= 5);
	time_t time_now = time(0);
	char *formated_time = ctime(&time_now);
	std::string level_text = levels[level];
	std::string level_color = level_colors[level];

    if (level >= log_level && enabled) {
        std::ofstream log_output(log_file);

        std::clog << level_color << level_text		<< NORMAL	<< TAB
            	  << BOLD 		 << formated_time	<< NORMAL	<< TAB
            	  << message						            << std::endl;
        
        log_output << level		<< TAB
        	   << formated_time << TAB
        	   << message       << std::endl;
    }
}

void logger::set_log_level(int level)
{
    log_level = level;
}

void logger::disable()
{
	enabled = false;
}

void logger::enable()
{
	enabled = true;
}

int logger::get_log_level()
{
	return log_level;
}

