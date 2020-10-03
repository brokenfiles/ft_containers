

#include "List.hpp"
#include "Vector.hpp"
#include <list>

int main()
{
	ft::Vector<int>::size_type sz;
	ft::Vector<int> vector;
	for (int i = 0; i < 4; ++i)
	{
		vector.push_back(i);
	}

	std::cout << "current capacity : " << vector.capacity() << std::endl;

	vector.resize(0);
	std::cout << "current capacity : " << vector.capacity() << std::endl;
	ft::Vector<int> two;
	two.insert(two.begin(), vector.begin(), vector.end());
	for (sz = 0; sz < two.size(); ++sz)
	{
		std::cout << "value at index " << sz << " : " << two[sz] << std::endl;
	}
}