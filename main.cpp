#include "Tests/list.hpp"
#include "List/List.hpp"
#include "Vector/Vector.hpp"
#include "Map/Map.hpp"
#include <list>
#include <vector>
#include <map>


void	print_vector(ft::Vector<int>::iterator it, ft::Vector<int>::iterator ite)
{
	while (it != ite)
	{
		std::cout << *it << std::endl;
		it++;
	}
}
void	print_vector(std::vector<int>::iterator it, std::vector<int>::iterator ite)
{
	while (it != ite)
	{
		std::cout << *it << std::endl;
		it++;
	}
}

int main()
{
//	exec_test_list<ft::List<int> >();
//	exec_test_list<std::list<int> >();
	ft::Vector<int> myvector (3,100);
	ft::Vector<int>::iterator it;

	it = myvector.begin();
	it = myvector.insert ( it , 200 );

	myvector.insert (it,(size_t)2,300);

	// "it" no longer valid, get a new one:
	it = myvector.begin();

	ft::Vector<int> anothervector (2,400);
	myvector.insert (it+2,anothervector.begin(),anothervector.end());

	int myarray [] = { 501,502,503 };
	myvector.insert (myvector.begin(), myarray, myarray+3);

	std::cout << "myvector contains:";
	for (it=myvector.begin(); it<myvector.end(); it++)
		std::cout << ' ' << *it;
	std::cout << '\n';

	return 0;
}