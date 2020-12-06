#include "Tests/list.hpp"
#include "Tests/map.hpp"
#include "List/List.hpp"
#include "Vector/Vector.hpp"
#include "Map/Map.hpp"
#include "Map/BST.hpp"
#include <list>
#include <vector>

typedef std::pair<int, std::string> pair_type;

typedef ft::BST<int, std::string>::Iterator iterator;
typedef ft::BST<int, std::string>::Node node_type;

int main()
{
//	exec_test_list<ft::List<int> >();
//	exec_test_list<std::list<int> >();
//	exec_test_map<ft::Map<int, int> >();
	exec_test_map<std::map<int, int> >();
//	map[2] = 10;
//	std::cout << "upper : " << map.lower_bound(2)->first << std::endl;
//	ft::Map<int, int>::iterator begin = map.begin();
//	ft::Map<int, int>::iterator end = map.end();
//	while (begin != end) {
//		std::cout << begin->first << " : " << begin->second << std::endl;
//		begin++;
//	}
//	std::cout << begin->first << std::endl;
//	std::cout << map[0] << std::endl;
//	std::cout << "map final size : " << map.size() << std::endl;
//
//	std::cout << "---" << std::endl;
//
//	std::map<int, int> Map;
//	Map[0] = 42;
//	Map[1] = 21;
//	Map[2] = 10;
//	std::cout << "upper : " << Map.lower_bound(2)->first << std::endl;

	return 0;
}