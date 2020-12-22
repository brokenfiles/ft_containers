#include "Tests/list.hpp"
#include "Tests/map.hpp"
#include "Tests/vector.hpp"
#include "List/List.hpp"
#include "Vector/Vector.hpp"
#include "Map/Map.hpp"
#include <list>

int main()
{
	exec_test_list<ft::list<int> >();
//	exec_test_list<std::list<int> >();
	std::list<std::string> map_tests;
//	map_tests.push_back("erase_test");
	exec_test_map<ft::map<int, int> >(map_tests);
	exec_test_vector<ft::vector<int> >();
	return 0;
}