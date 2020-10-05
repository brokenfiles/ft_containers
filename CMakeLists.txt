cmake_minimum_required(VERSION 3.15)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)
#set (CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")

add_executable(ft_containers main.cpp Vector.hpp Stack.hpp List.hpp colors.hpp utils.hpp Queue.hpp MutantStack.hpp)
