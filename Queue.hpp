#include "List.hpp"

namespace ft
{
	template <class T, class Container = List<T> >
	class Queue
	{
	public:
		typedef Container									container_type;
		typedef typename container_type::value_type			value_type;
		typedef typename container_type::size_type			size_type;
		typedef typename container_type::reference			reference;
		typedef typename container_type::const_reference	const_reference;

	protected:
		container_type c_container;

	public:
		Queue (const container_type& ctnr = container_type())
		{ this->c_container = ctnr; }

		Queue() { }

		Queue operator= (const Queue rhs)
				{ this->c_container = rhs.c_container; }

		virtual ~Queue() { }

		bool empty() const
		{ return this->c_container.empty(); }

		void push (const_reference val)
		{ this->c_container.push_back(val); }

		size_type size() const
		{ return this->c_container.size(); }

		reference front()
		{ return this->c_container.front(); }

		const_reference front() const
		{ return this->c_container.front(); }

		reference back()
		{ return this->c_container.back(); }

		const_reference back() const
		{ return this->c_container.back(); }

		void pop()
		{ return this->c_container.pop_back(); }

	};

	template <class T, class Container>
	bool operator==(Queue<T, Container> &lhs, Queue<T, Container> &rhs)
	{
		return (lhs.c_container == rhs.c_container);
	}

	template <class T, class Container>
	bool operator> (Queue<T, Container> &lhs, Queue<T, Container> &rhs)
	{
		return (lhs.c_container > rhs.c_container);
	}

	template <class T, class Container>
	bool operator>=(Queue<T, Container> &lhs, Queue<T, Container> &rhs)
	{
		return (lhs.c_container >= rhs.c_container);
	}

	template <class T, class Container>
	bool operator< (Queue<T, Container> &lhs, Queue<T, Container> &rhs)
	{
		return (lhs.c_container < rhs.c_container);
	}

	template <class T, class Container>
	bool operator<=(Queue<T, Container> &lhs, Queue<T, Container> &rhs)
	{
		return (lhs.c_container == rhs.c_container);
	}

	template <class T, class Container>
	bool operator!=(Queue<T, Container> &lhs, Queue<T, Container> &rhs)
	{
		return (lhs.c_container == rhs.c_container);
	}
}