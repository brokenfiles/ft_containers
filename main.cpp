#include "Tests/list.hpp"
#include "Tests/map.hpp"
#include "List/List.hpp"
#include "Vector/Vector.hpp"
#include "Map/Map.hpp"
#include "Map/BST.hpp"
#include <list>
#include <vector>

typedef std::pair<int, std::string> pair_type;

typedef ft::BST<int, int>::Iterator iterator;
typedef ft::BST<int, const int>::Iterator const_iterator;
typedef ft::BST<int, std::string>::Node node_type;

int main()
{
//	exec_test_list<ft::List<int> >();
//	exec_test_list<std::list<int> >();
//	std::list<std::string> map_tests;
//	map_tests.push_back("erase_test");
//	exec_test_map<ft::Map<int, int> >(map_tests);
//	typedef ft::List<int>::reverse_iterator reverse_iterator;
//	ft::List<int> list;
//	list.push_back(42);
//	list.push_front(5);
//	assert(list.size() == 2);
//	reverse_iterator rend = list.rbegin();
//	rend++;
//	assert(*rend == 5);
//	rend++;
//	assert(*rend == 42);
	ft::List<int> list;
	list.push_back(42);
	list.push_back(5);
	ft::List<int>::iterator begin = list.begin();
	for (int i = 0; i < 10; ++i)
	{
		std::cout << *begin << std::endl;
		begin++;
	}

//	exec_test_map<std::map<int, int> >(map_tests);
//	ft::Map<int, int> map;
//	const_iterator cit = map.begin();

//	ft::Map<int, int> map;
//	typedef ft::Map<int, int>::const_reverse_iterator map_iterator;
//	map[0] = 42;
//	map[-1] = 42;
//	map[5] = 10;
//	map[2] = 10;
//	map[7] = 10;
//	map[8] = 10;
////	map.print();
//	map_iterator begin = map.rbegin();
//	while (begin != map.rend()) {
//		std::cout << begin->first << " : " << begin->second << std::endl;
//		begin++;
//	}

//	ft::List<int> list;
//	list.push_back(42);
//	list.push_back(21);
//	list.push_back(10);
//	list.push_back(5);
//	list.push_back(3);
//	list.push_back(2);
//	list.push_back(1);
//	list.push_back(0);
//	typedef ft::List<int>::const_reverse_iterator const_reverse_iterator;
//	const_reverse_iterator it = list.rbegin();
//	while (it != list.rend()) {
//		std::cout << *it ;
//		it ++;
//		if (it != list.rend()) {
//			std::cout << ", ";
//		}
//	}
//	std::cout << std::endl;

//	ft::Vector<int> vec;
//	vec.push_back(42);
//	vec.push_back(54);
//	typedef ft::Vector<int>::const_iterator const_vector_iterator;
//	const_vector_iterator cit = vec.begin();

	return 0;
}