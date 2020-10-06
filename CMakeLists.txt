cmake_minimum_required(VERSION 3.15)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)
#set (CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")

add_executable(ft_containers main.cpp Vector/Vector.hpp Stack/Stack.hpp List/List.hpp colors.hpp utils.hpp Queue/Queue.hpp Map/Map.hpp Map/Less.hpp)
