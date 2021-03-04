#include <iostream>
#include <stack>

void printStack(std::stack<int> &st)
{
	while(st.size())
	{
		std::cout << st.top() << std::endl;
		st.pop();
	}
}


int stack()
{
	std::stack<int> st;
	for (int i = 0; i < 5; ++i)
	{
		st.push(i);
		std::cout << st.top() << "\n";
	}
	printStack(st);
}