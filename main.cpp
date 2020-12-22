#include "Tests/list.hpp"
#include "Tests/map.hpp"
#include "Tests/vector.hpp"
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
//	typedef ft::List<int>::reverse_iterator reverse_iterator;

	exec_test_list<ft::list<int> >();
//	exec_test_list<std::list<int> >();
	std::list<std::string> map_tests;
//	map_tests.push_back("erase_test");
	exec_test_map<ft::map<int, int> >(map_tests);
	exec_test_vector<ft::vector<int> >();
	return 0;
}