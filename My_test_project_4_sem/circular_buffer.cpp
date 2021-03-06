#include "circular_buffer.h"
#include <iostream>
#include <boost/circular_buffer.hpp>
#include <ctime>
#include "time_stamp.h"
#include <string>

using circular_buffer = boost::circular_buffer<std::pair<std::string, std::string>>;

void circ_buff()
{
    int N;
    std::cout << "You can enter capacity of the buffer: \n";
    std::cin >> N;

    std::cout << "If you want to stop, please write 'I am bored' \n";
    std::cout << "Enter logins: \n";

    circular_buffer users(N);
    std::string login;
    std::getline(std::cin, login);

    while (login != "I am bored")
    {
        users.push_back(std::make_pair(login, time_stamp()));
        std::getline(std::cin, login);
    }

    for (auto i : users)
        std::cout << i.first << " " << i.second << "\n";
}