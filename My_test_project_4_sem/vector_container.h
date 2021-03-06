#ifndef VECTOR_CONTAINER
#define VECTOR_CONTAINER
#include <vector>
#include <deque>
#include <list>
#include <fstream>

void vec_out(int n, const std::vector<int>& v);
void vector();

void do_all(std::ofstream& fout, std::vector<long double>& vec, std::deque<long double>& deq, std::list<long double>& lis, int& N);
void container();

#endif // !VECTOR_CONTAINER
