#ifndef TIME_STAMP
#define TIME_STAMP
#include <ctime>
#include <iostream>

std::tm localtime_xp(std::time_t timer);
std::string time_stamp(const std::string& fmt = "%d:%m:%Y %T");

#endif // !TIME_STAMP

