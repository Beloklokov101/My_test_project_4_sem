
#include <iostream>
//#include <boost/align.hpp>
#include <vector>
#include <algorithm>

int main()
{
    std::cout << "N:";
    int N;
    std::cin >> N;

    std::vector<int> a(N);
    std::vector<int> b(N);
    
    std::cout << "a: ";
    for (int i = 0; i < N; ++i) {
        std::cin >> a[i];
    }

    std::cout << "b: ";
    for (int i = 0; i < N; ++i) {
        std::cin >> b[i];
    }

    auto its = b.begin();
    auto itr = b.rbegin();
    auto ita = a.begin();

    for (int i = 0; i < N / 2; ++i) {
        std::iter_swap(its, itr);
        its++;
        itr++;
    }
    its = b.begin();

    for (int i = 0; i < N; ++i) {
        std::iter_swap(ita, its);
        ita++;
        its++;
    }

    //std::reverse(b.begin(), b.end());
    //a.swap(b);

    std::cout << std::endl << "a  b" << std::endl;
    for (int i = 0; i < N; ++i) {
        std::cout << a[i] << " " << b[i] << std::endl;
    }
}
//Master branch rebase test commit