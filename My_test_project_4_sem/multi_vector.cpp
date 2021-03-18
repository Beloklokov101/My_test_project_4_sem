//#include "multi_vector.h"

#include <vector>
#include <algorithm>
#include <iostream>
#include <typeinfo>
#include <deque>
#include "boost/multi_array.hpp"


template<size_t dimcount, typename T>
class multi_vector
{
public:
	//В итоге эти две строчки не нужны получаются
	typedef std::vector< typename multi_vector<dimcount - 1, T>::type> type;
	std::vector<type> vec;

	//Vector with point-s on next subobjects
	std::vector<multi_vector<dimcount - 1, T>*> next_vec;
	//Number of subobject from next_vec where you can add next item
	int col_to_push;
	//Size of the object
	const int size;

	multi_vector(std::vector<int> size_arr) : size(size_arr[dimcount])
	{
		//Это можно убрать
		vec.reserve(size);
		for (int i = 0; i < size; ++i)
		{
			multi_vector<dimcount - 1, T>* n_vec = new multi_vector<dimcount - 1, T>(size_arr);
			next_vec.push_back(n_vec);
			std::cout << "Object number " << dimcount << " " << i << " create\n";

			//И это соответственно тоже
			vec.push_back((*n_vec).get_vec());
		}
		col_to_push = 0;
	}

	~multi_vector()
	{
		for (int i = 0; i < size; ++i)
		{
			delete next_vec[i];
			std::cout << "Object number " << dimcount << " " << i << " delete\n";
		}
	}
	

	//Эта функция тоже факту ничего не делает полезного
	std::vector<type> get_vec()
	{
		return vec;
	}
	
	//Allow to adress like arr[0][1][2]
	multi_vector<dimcount - 1, T>& operator[](const int i)
	{
		return *next_vec[i];
	}

	//You can call item by his number it was added and by key 'f'
	T& operator()(const int num, char key)
	{
		if (key == 'f')
		{
			int yet = num;
			std::deque<int> sizes = (*next_vec[0]).get_size();
			std::reverse(sizes.begin(), sizes.end());
			for (int i : sizes)
				yet = yet / i;
			int new_num = num - yet * (*next_vec[0]).num_of_el();
			return (*next_vec[yet])(new_num, 'f');
		}
		else
		{
			std::cout << "Smth went wrong\n";
			//return 0;
		}
	}

	//Adding item
	void push_back(const T num)
	{
		if (col_to_push < size)
		{
			(*next_vec[col_to_push]).push_back(num);
			if ((*(next_vec[col_to_push])).col_to_push == (*(next_vec[col_to_push])).size)
				col_to_push++;
		}
	}

	//Removing last item
	void pop_back()
	{
		if (col_to_push >= size)
		{
			col_to_push = size - 1;
			(*next_vec[col_to_push]).pop_back();
		}
		else if ((*next_vec[col_to_push]).size_v() == 0)
		{
			if (col_to_push > 0)
			{
				col_to_push = size - 1;
				(*next_vec[col_to_push]).pop_back();
			}
		}
		else
		{
			(*next_vec[col_to_push]).pop_back();
		}
	}

	//Return deque with sizes below this object (subobjects)
	std::deque<int> get_size()
	{
		std::deque<int> sizes = (*next_vec[0]).get_size();
		sizes.push_front(size);
		return sizes;
	}

	//Return multiplication of sizes below this object (subobjects)
	int num_of_el()
	{
		int num = (*next_vec[0]).num_of_el();
		num *= size;
		return num;
	}

	//Return number of added elements below this object (subobjects)
	int size_v()
	{
		int num = col_to_push * (*next_vec[0]).num_of_el() + (*next_vec[col_to_push]).size_v();
		return num;
	}
};

//Как я понимаю, в результате только на самых низких уровнях появляются векторы, в которых лежат элементы
//До этого все хранится в векторах, которые хранят ссылки на элементы, под которых выделили память
//Но не векторы, хранящие векторы, к чему я планировал прийти
//И мне сложно сказать, насколько вообще так хранить данные эффективно
template<typename T>
class multi_vector<0, T>
{
public:
	typedef T type;
	std::vector<type> vec;
	int col_to_push;
	const int size;

	multi_vector(std::vector<int> size_arr) : size(size_arr[0])
	{
		vec.reserve(size);
		col_to_push = 0;
	}

	~multi_vector() {}

	std::vector<type> get_vec()
	{
		return vec;
	}

	T& operator[](const int i)
	{
		return vec[i];
	}

	T& operator()(const int num, char key)
	{
		return vec[num];
	}

	void push_back(const T num)
	{
		if (col_to_push < size)
		{
			vec.push_back(num);
			col_to_push++;
		}
	}

	void pop_back()
	{
		vec.pop_back();
		col_to_push--;
	}

	std::deque<int> get_size()
	{
		std::deque<int> sizes;
		sizes.push_front(size);
		return sizes;
	}

	int num_of_el()
	{
		return size;
	}

	int size_v()
	{
		return vec.size();
	}
};


template<typename T, int N>
void fill_multi_array(boost::multi_array<T, N>& m_arr, multi_vector<N - 1, T>& vec)
{
	int vec_size = vec.size_v();
	auto orig = m_arr.origin();

	int j = 0;
	for (auto i = orig; i < orig + vec_size; ++i)
	{
		*i = vec(j, 'f');
		j++;
	}
}


int main()
{
	//Type of the item
	typedef int T;
	//How deep will your vector / array be
	const int N = 3;
	//Sizes of "ojects", dimensions
	std::vector<int> size = { 2, 3, 4 };

	//Init. multi_vector
	std::reverse(size.begin(), size.end());
	
	multi_vector<N - 1, T> vec3(size);

	std::reverse(size.begin(), size.end());

	//Check functions
	std::cout << "\nSizes: ";
	std::deque<int> deq = vec3.get_size();
	for (int i : deq)
		std::cout << i << " ";
	std::cout << "\nNumber of elements: " << vec3.num_of_el() << "\n";

	//Adding elemets
	std::cout << "Vec. size: " << vec3.size_v() << " ";
	for (int i = 0; i < 10; i++)
	{
		vec3.push_back(i);
		std::cout << "Vec. size: " << vec3.size_v() << "\n";
	}

	//Check of adding
	std::cout << "\n";
	for (int i = 0; i < 10; ++i)
		std::cout << vec3(i, 'f') << " ";
	std::cout << "\n";

	//Init. multi_array
	typedef boost::multi_array<T, N> array_type;
	boost::array<array_type::index, N> shape = { { 2, 3, 4 } };

	array_type m_arr(shape);
	

	//Filling multi_array with multi_vector
	fill_multi_array<T, N>(m_arr, vec3);

	//Check of filling
	std::cout << "\n";
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 3; ++j)
			for (int k = 0; k < 4; ++k)
				std::cout << m_arr[i][j][k] << " ";
	}
	std::cout << "\n";

}