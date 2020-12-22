cmake_minimum_required(VERSION 3.15)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)
set (CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")

add_executable(ft_containers Tests/main.cpp Vector/Vector.hpp Stack/Stack.hpp List/List.hpp colors.hpp utils.hpp Queue/Queue.hpp Map/Map.hpp Map/Less.hpp Tests/Tester.hpp Tests/handlers/map.hpp Tests/handlers/list.hpp Tests/handlers/vector.hpp Tests/unit_tests/queue_tests.hpp Tests/handlers/stack.hpp Tests/unit_tests/stack_tests.hpp Tests/handlers/queue.hpp Tests/unit_tests/list_tests.hpp Tests/unit_tests/vector_tests.hpp Map/BST.hpp Map/Pair.hpp List/ListIterators.hpp Map/MapIterators.hpp Vector/VectorIterators.hpp Tests/Tester_Include.hpp)
