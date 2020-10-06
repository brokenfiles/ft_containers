#include "List/List.hpp"
#include "Vector/Vector.hpp"
#include "Stack/Stack.hpp"
#include "Queue/Queue.hpp"
#include <list>
#include <queue>

bool pred(std::string &val)
{
	return (val == "comment ca va");
}

int main()
{
	ft::Queue<int> queue;
	queue.push(5);
	queue.push(10);
	queue.push(15);
	queue.push(20);

	return 0;
}

int other_main()
{
	ft::Vector<std::string>::size_type sz;
	ft::Vector<std::string> vector;
	for (int i = 0; i < 3; ++i)
	 { vector.push_back("bonjour " + std::to_string(i)); }

	vector.insert(vector.end() - (vector.size() / 2), 3, "yo lekip");
	ft::Vector<std::string> two = vector;
//	vector.pop_back();
//	vector.erase(vector.end() - 1);
//	vector.clear();
//	two.insert(two.begin(), vector.begin(), vector.end());
//	two.erase(two.begin() + 1, two.end() - 1);
	std::cout << "two len : " << two.size() << std::endl;
	std::cout << "two cap : " << two.capacity() << std::endl;
	std::cout << "back val : " << two.back() << std::endl;
	for (sz = 0; sz < two.size(); ++sz)
	 { std::cout << "value at index " << sz << " : " << two[sz] << std::endl; }
	return 0;
}