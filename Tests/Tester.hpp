#ifndef TESTER_HPP
# define TESTER_HPP

# include <map>
# include <cassert>
# include <iostream>
# include <list>
# include <unistd.h>
# include <cstdlib>
# include <wait.h>

typedef void (*fn_ptr)();
typedef std::list<std::string> wanted_tests_type;
void announce_test(const std::string &test_name);
void success_test(const std::string &test_name);
void launch_test(const std::string &func_name);
void error_test(const std::string &test_name, const int &status);
struct Global
{
	std::map<std::string, fn_ptr> funcs;

	void start_test(wanted_tests_type tests)
	{
		if (tests.empty())
		{
			std::map<std::string, fn_ptr>::iterator begin = funcs.begin();
			while (begin != funcs.end())
			{
				launch_test(begin->first);
				begin++;
			}
		}
		else
		{
			wanted_tests_type::iterator begin = tests.begin();
			while (begin != tests.end())
			{
				launch_test(*begin);
				begin++;
			}
		}
	}
};
Global global;

void register_test(const std::string &func_name, fn_ptr ptr)
{
	global.funcs[func_name] = ptr;
}

void launch_test(const std::string &func_name)
{
	int status;
	if (global.funcs.find(func_name) == global.funcs.end())
	{ throw std::invalid_argument("\"" + func_name + "\" function is not registered so it cannot be launched"); }
	announce_test(func_name);
	pid_t pid = fork();
	if (pid == 0)
	{
		global.funcs[func_name]();
		exit(0);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{ success_test(func_name); }
	else
	{
		error_test(func_name, status);
		exit(status);
	}
}

void register_test_and_launch(const std::string &func_name, fn_ptr ptr)
{
	register_test(func_name, ptr);
	launch_test(func_name);
}

void new_type(const std::string &class_name)
{
	global.funcs.clear();
	std::cout << "\033[01;36m" << "[ TESTS : " << class_name << " ]\033[0;0m" << std::endl;
}

void category(const std::string &category)
{
	std::cout << "\033[01;33m" << "|-- category : " << category << "\033[0;0m" << std::endl;
}

void announce_test(const std::string &test_name)
{
	std::cout << "\033[0;35m" << "|- starting test " << test_name << "\033[0;0m" << std::endl;
}

void success_test(const std::string &test_name)
{
	std::cout << "\033[01;32m" << "|- \033[0;32m[OK]\033[01;32m test " << test_name << " is a success\033[0;0m"
			  << std::endl;
}

void error_test(const std::string &test_name, const int &status)
{
	if (status == SIGSEGV)
		std::cout << "⚠️ There is a segfault in your container (or maybe in the tests)" << std::endl;
	std::cout << "\033[01;31m" << "|- \033[0;31m[KO]\033[01;31m test " << test_name << " contains an error "
			  << "(status code : " << status << ")" << "\033[0;0m" << std::endl;
}

#endif