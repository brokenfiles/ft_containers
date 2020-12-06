#ifndef MAP_TESTS_HPP
# define MAP_TESTS_HPP

# include "Tester.hpp"


/*
template<class List>
void template_test()
{
	List list;
}
 */

template<class Map>
void insert_and_change_values()
{
	Map map;
	assert(map.size() == 0);
	map[0] = 42;
	assert(map[0] == 42);
	map[0] = 21;
	assert(map[0] == 21);
	assert(map.size() == 1);
	map[1000] = 21;
	assert(map.size() == 2);
}

#endif