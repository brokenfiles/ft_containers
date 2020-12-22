#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <map>
# include "Tester.hpp"
# include "vector_tests.hpp"

template<class Vector>
void exec_test_vector(wanted_tests_type tests = wanted_tests_type())
{
	new_type("Vector");
	{
		//register tests
		register_test("insert_vector", insert_vector<Vector>);
		register_test("capacity_vector_tests", capacity_vector_tests<Vector>);
		register_test("reserve_vector_tests", reserve_vector_tests<Vector>);
		register_test("iterators_vector_tests", iterators_vector_tests<Vector>);
		register_test("element_access_vector_tests", element_access_vector_tests<Vector>);
		register_test("resize_vector_tests", resize_vector_tests<Vector>);
		register_test("constructors_vector_tests", constructors_vector_tests<Vector>);
		register_test("operators_vector_tests", operators_vector_tests<Vector>);
		register_test("swap_vector_tests", swap_vector_tests<Vector>);
		register_test("clear_vector_tests", clear_vector_tests<Vector>);
		register_test("pop_back_vector_tests", pop_back_vector_tests<Vector>);
	}
	//launch tests
	global.start_test(tests);
}

#endif