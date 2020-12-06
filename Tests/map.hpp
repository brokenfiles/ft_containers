#ifndef MAP_HPP
# define MAP_HPP

#include "Tester.hpp"
#include "map_tests.hpp"

template <class Map>
void exec_test_map(wanted_tests_type tests = wanted_tests_type())
{
	new_type("Map");
	{
		//register tests
		register_test("insert_and_change_values", insert_and_change_values<Map>);
	}
	//launch tests
	global.start_test(tests);
}
#endif