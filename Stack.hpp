#include <deque>
#include "List.hpp"

namespace ft
{
	template<class T, class Container = ft::List<T> >
	class Stack
	{
	public:
		typedef T value_type;
		typedef Container container_type;
		typedef size_t size_type;
	private:
		container_type container;
	public:
		explicit Stack(const container_type &ctnr = container_type())
		{
			this->container = ctnr;
		}

		Stack(const Stack &stack)
		{
			*this = stack;
		}

		~Stack()
		{
			return;
		}

		Stack &operator=(const Stack &stack)
		{
			this->container = stack.container;
			return (*this);
		}

		value_type &top()
		{
			return (this->container.back());
		}

		const value_type &top() const
		{
			return (this->container.back());
		}

		bool empty() const
		{
			return (this->container.empty());
		}

		size_type size() const
		{
			return (this->container.size());
		}

		void push(const value_type &val)
		{
			this->container.push_back(val);
		}

		void pop()
		{
			this->container.pop_back();
		}
	};

	template<class T, class Container>
	bool operator==(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs)
	{
		return (lhs == rhs);
	}

	template<class T, class Container>
	bool operator!=(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs)
	{
		return (lhs != rhs);
	}

	template<class T, class Container>
	bool operator<(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs)
	{
		return (lhs < rhs);
	}

	template<class T, class Container>
	bool operator<=(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs)
	{
		return (lhs <= rhs);
	}

	template<class T, class Container>
	bool operator>(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs)
	{
		return (lhs > rhs);
	}

	template<class T, class Container>
	bool operator>=(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs)
	{
		return (lhs >= rhs);
	}
}
