#include <iostream>
#include <boost/circular_buffer.hpp>
#include "boost_buffer.h"

using circular_buffer = boost::circular_buffer<int>;


void boost_buffer()
{
	circular_buffer cb{ 3 };
	for (int i = 0; i < 4; ++i)
	cb.push_back(i);

	std::cout << std::boolalpha << cb.is_linearized() << "\n";

	circular_buffer::array_range ar1, ar2;
	ar1 = cb.array_one();
	ar2 = cb.array_two();
	
	std::cout << *ar1.first << ";" << *ar2.first << "\n";
	std::cout << ar1.second << ";" << ar2.second << "\n";

	for (int i : cb)
		std::cout << i << " ";
	std::cout << "\n";

	cb.linearize();

	ar1 = cb.array_one();
	ar2 = cb.array_two();

	std::cout << ar1.second << ";" << ar2.second << "\n";

	for (int i = 0; i < 2; i++)
		std::cout << ar2.first[i] << " ";
	std::cout << "\n";
}