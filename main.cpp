#include <iostream>
#include "Stack.hpp"

int main()
{
	ft::Stack<int> stack;
	stack.push(45);
	std::cout << stack.top() << std::endl;
}
