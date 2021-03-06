#ifndef CIRC_BUFF
#define CIRC_BUFF
#include <iostream>
#include <ctime>

inline std::tm localtime_xp(std::time_t timer);
inline std::string time_stamp(const std::string& fmt);
void circ_buff();

#endif // !CIRC_BUFF

