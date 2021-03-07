#include "vector_set.h"
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <random>
#include <chrono>
#include "Timer.h"
#include <fstream>
#include <iomanip>

void do_all(std::ofstream& fout, const int& N)
{
	std::vector<int> fill;
	for (int i = 0; i < N; ++i)	fill.push_back(i);

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	std::shuffle(fill.begin(), fill.end(), std::default_random_engine(seed));

	std::vector<long float> vec;
	std::set<long float> st;

	Timer t;
	for (int i : fill)
	{
		st.insert(i);
	}
	std::cout << N << "		" << t.elapsed();
	fout << N << "		" << t.elapsed();


	for (int i : fill)
	{
		vec.push_back(i);
	}

	t.reset();
	std::sort(vec.begin(), vec.end());
	std::cout << "	" << t.elapsed() << "\n";
	fout << "	" << t.elapsed() << "\n";
	//Difference in time because of std::cout?

}


void vec_set()
{
	int N;
	int rep;

	std::cout << "Please write number of repeats: \n";
	std::cin >> rep;

	std::cout << "Please write number of elements: \n";
	std::cin >> N;

	std::ofstream fout("vec_set.txt", std::ios_base::out | std::ios_base::trunc);

	if (fout.is_open())
	{

		std::cout << "\nN		SET		VEC\n";
		fout << "N		SET		VEC\n";

		for (int i = 0; i < rep; ++i)
		{
			do_all(fout, N * (i + 1));
		}
		fout.close();
	}
	else
		std::cout << "File is unavailable\n";
}