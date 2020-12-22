#include <deque>
#include "../List/List.hpp"

namespace ft
{
	template<class T, class Container = ft::list<T> >
	class stack
	{
	public:
		typedef T value_type;
		typedef Container container_type;
		typedef size_t size_type;
	private:
		container_type container;
	public:
		explicit stack(const container_type &ctnr = container_type())
		{
			this->container = ctnr;
		}

		stack(const stack &stack)
		{
			*this = stack;
		}

		~stack()
		{
			return;
		}

		stack &operator=(const stack &stack)
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

		friend bool operator==(stack<T, Container> &lhs, stack<T, Container> &rhs)
		{
			return (lhs.container == rhs.container);
		}

		friend bool operator!=(stack<T, Container> &lhs, stack<T, Container> &rhs)
		{
			return (lhs.container != rhs.container);
		}

		friend bool operator<(stack<T, Container> &lhs, stack<T, Container> &rhs)
		{
			return (lhs.container < rhs.container);
		}

		friend bool operator<=(stack<T, Container> &lhs, stack<T, Container> &rhs)
		{
			return (lhs.container <= rhs.container);
		}

		friend bool operator>(stack<T, Container> &lhs, stack<T, Container> &rhs)
		{
			return (lhs.container > rhs.container);
		}

		friend bool operator>=(stack<T, Container> &lhs, stack<T, Container> &rhs)
		{
			return (lhs.container >= rhs.container);
		}

	};

}
