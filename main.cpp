#include "Tests/list.hpp"
#include "List/List.hpp"
#include "Vector/Vector.hpp"
#include "Map/Map.hpp"
#include <list>
#include <vector>
#include <map>

int main()
{
	exec_test_list<ft::List<int> >();
	exec_test_list<std::list<int> >();
	return 0;
}