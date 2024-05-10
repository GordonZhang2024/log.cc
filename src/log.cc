#include "log.h"

void logger::log(const char *level, const char *message)
{
	time_t time_now = time(0);
	char *formated_time = ctime(&time_now);
	clog << level			<< TAB
		 << formated_time   << TAB
		 << message			<< endl;
}

void logger::add_callback_file(string file)
{
	callback_files.push_back(file);
}

void logger::show_callback_files()
{
	for (int i = 0; i < callback_files.size(); ++i) {
		string current_file = callback_files[i];
		cout << current_file << endl;
	}
}

