#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include <fstream>
#include <iomanip>

#include "../../aux_files/Timer.h"

/* Paste to main,
// don't forget to add Timer from aux_files to your project
#include "h_w/5-6_sem/vector_container.h"
int main(){
	vector();
	container();
	return 0;
}
*/

void vec_out(int n, const std::vector<int>& v)
{
	std::cout << "v" << n << " size: " << v.size() << " capacity: " << v.capacity() << "\n";
}

void vector()
{
	std::vector<int> v1;
	std::vector<int> v2;
	v2.reserve(50);
	
	vec_out(1, v1);
	vec_out(2, v2);
	std::cout << "\n";

	size_t cap1 = v1.capacity();
	size_t cap2 = v2.capacity();

	for (int i = 0; i < 200; ++i)
	{
		v1.push_back(i);
		v2.push_back(i);

		if ((cap1 != v1.capacity()) || (cap2 != v2.capacity()))
		{
			vec_out(1, v1);
			vec_out(2, v2);
			std::cout << "\n";

			cap1 = v1.capacity();
			cap2 = v2.capacity();
		}
	}


}

void do_all(std::ofstream& fout, std::vector<long double>& vec, std::deque<long double>& deq, std::list<long double>& lis, const int &N)
{
	vec.clear();
	deq.clear();
	lis.clear();

	for (int i = 0; i < N; ++i)
	{
		long double num = std::rand();
		vec.push_back(num);
		deq.push_back(num);
		lis.push_back(num);
	}

	Timer t;

	sort(vec.begin(), vec.end());

	std::cout << "Vector: N: " << N << " Time: " << t.elapsed() << "\n";
	fout << "Vector: N: " << N << " Time: " << t.elapsed() << "\n";
	t.reset();

	sort(deq.begin(), deq.end());

	std::cout << "Deque:  N: " << N << " Time: " << t.elapsed() << "\n";
	fout << "Deque:  N: " << N << " Time: " << t.elapsed() << "\n";
	t.reset();

	lis.sort();

	std::cout << "List:   N: " << N << " Time: " << t.elapsed() << "\n" << "\n";
	fout << "List:   N: " << N << " Time: " << t.elapsed() << "\n" << "\n";
}

void container()
{
	int N = 100000;
	int count = 5;
	std::vector<long double> vec;
	std::deque<long double> deq;
	std::list<long double> lis;
	vec.reserve(N*count);

	const char* path = "inf_4_sem/h_w/5-6_sem/vector_container.txt";
	std::ofstream fout(path, std::ios_base::out | std::ios_base::trunc);
	
	if (fout.is_open())
	{
		for (int i = 0; i < count; i++)
		{
			do_all(fout, vec, deq, lis, N * (i + 1));
		}
	}

	fout.close();
}