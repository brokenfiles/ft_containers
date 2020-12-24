
#ifndef FT_CONTAINERS_LIST_HPP
#define FT_CONTAINERS_LIST_HPP

#include <iostream>
#include <limits>
#include "ListIterators.hpp"

namespace ft
{
	template<class T>
	int _sort_less_than(T first, T second)
	{ return (first < second); }

	template<class T>
	class list
	{

	public:
		typedef T                           value_type;
		typedef size_t                      size_type;
		typedef std::ptrdiff_t              difference_type;
		typedef value_type                  &reference;
		typedef const value_type            &const_reference;
		typedef value_type                  *pointer;
		typedef const value_type            *const_pointer;
		typedef ListIterator<T>             iterator;
		typedef ConstListIterator<T>        const_iterator;
		typedef ReverseListIterator<T>      reverse_iterator;
		typedef ConstReverseListIterator<T> const_reverse_iterator;

	protected:
		Node<value_type> *c_begin;
		Node<value_type> *c_end;
		size_type        c_len;

	private:

		/**
		 * Initiate the chained list
		 */
		void init_chained_link()
		{
			this->c_end   = new Node<value_type>();
			this->c_begin = this->c_end;
			this->bounds();
		}

		void bounds()
		{
			this->c_begin     = this->c_end;
			this->c_end->prev = this->c_begin;
			this->c_end->next = this->c_begin;
		}

		reference _get(size_type n)
		{
			if (n < 0 || n >= this->c_len)
				throw std::invalid_argument("argument n is invalid (< 0 || >= c_len)");
			iterator       begin = this->begin();
			for (size_type i     = 0; i < n; ++i)
				begin++;
			return (begin.get_node()->content);
		}

		template<typename C>
		void swap(C &one, C &second)
		{
			C tmp = second;
			second = one;
			one    = tmp;
		}

	public:
		/*
		 * Colpien
		 */

		/**
		 * empty container constructor (default)
		 */
		list()
		{
			this->c_begin = NULL;
			this->c_end   = NULL;
			this->c_len   = 0;
			this->init_chained_link();
		}

		/**
		 * Class destructor
		 * This destroys all container elements
		 * deallocates all the storage capacity allocated by the list container using its allocator.
		 * @param NULL
		 */
		virtual ~list()
		{
			if (this->size() > 0)
				delete this->c_end;
			this->clear();
		}

		/**
		 * fill constructor
		 * constructs a container with n elements (each element is a copy of val)
		 * @param n number of elements
		 * @param val value to insert
		 */
		list(size_type n, const value_type &val = value_type())
		{
			this->c_begin = NULL;
			this->c_end   = NULL;
			this->c_len   = 0;
			this->init_chained_link();
			this->assign(n, val);
		}

		/**
		 * range constructor
		 * constructs a container with as many elements as the range (first, last)
		 * with each element constructed from its corresponding element in that range, in the same order
		 * @tparam InputIterator iterator class
		 * @param first first iterator (begin of the range)
		 * @param last last iterator (end of the range)
		 */
		template<class InputIterator>
		list(InputIterator first, InputIterator last)
		{
			this->c_begin = NULL;
			this->c_end   = NULL;
			this->c_len   = 0;
			this->init_chained_link();
			this->assign(first, last);
		}

		/**
		 * copy constructor
		 * Constructs a container with a copy of each of the elements in x in the same order
		 * @param x other list to copy
		 */
		list(list &x)
		{
			this->c_begin = NULL;
			this->c_end   = NULL;
			this->c_len   = 0;
			this->init_chained_link();
			this->assign(x.begin(), x.end());
		}

		/*
		 * Assignation
		 */

		/**
		 * Assignation = function
		 * Assigns new contents to the container
		 * replacing its current contents
		 * modifying its size accordingly
		 * @param x other list to copy
		 * @return current instance
		 */
		list &operator=(const list &x)
		{
			this->c_begin = x.c_begin;
			this->c_end   = x.c_end;
			this->c_len   = x.c_len;
			return (*this);
		}

		/*
		 * Iteratorsm
		 */

		iterator begin()
		{ return (iterator(this->c_begin)); }

		const_iterator begin() const
		{ return (const_iterator(this->c_begin)); }

		iterator end()
		{ return (iterator(this->c_end)); }

		const_iterator end() const
		{ return (const_iterator(this->c_end)); }

		reverse_iterator rbegin()
		{ return (reverse_iterator(this->c_end->prev)); }

		const_reverse_iterator rbegin() const
		{ return (const_reverse_iterator(this->c_end->prev)); }

		reverse_iterator rend()
		{ return (reverse_iterator(this->c_begin->prev)); }

		const_reverse_iterator rend() const
		{ return (const_reverse_iterator(this->c_begin->prev)); }

		/*
		 * Public functions
		 */

		/*
		 * Capacity
		 */

		/**
		 * Returns whether the list container is empty (i.e. whether its size is 0)
		 * @return bool (true if the container size is 0, false otherwise)
		 */
		bool empty() const
		{
			return (this->c_len == 0);
		}

		/**
		 * @return size_type (The number of elements in the container)
		 */
		size_type size() const
		{
			return (this->c_len);
		}

		/**
		 * used to know the maximum potential size the container can reach\
		 *   due to known system or library implementation limitations
		 * @return size_type (The maximum number of elements the object can hold as content)
		 */
		size_type max_size() const
		{
			return std::numeric_limits<size_type>::max() / (sizeof(this->c_begin));
		}

		/*
		 * Element access
		 */

		/**
		 * @return reference (a reference to the first element in the list container)
		 */
		reference front()
		{
			return (this->c_begin->content);
		}

		/**
		 * @return const_reference (a reference to the first element in the list container)
		 */
		const_reference front() const
		{
			return (this->c_begin->content);
		}

		/**
		 * @return reference (a reference to the last element in the list container)
		 */
		reference back()
		{
			if (this->empty()) return (this->front());
			else return (this->c_end->prev->content);
		}

		/**
		 * @return const_reference (a reference to the last element in the list container)
		 */
		const_reference back() const
		{
			if (this->empty()) return (this->front());
			else return (this->c_end->prev->content);
		}

		/*
		 * Modifiers
		 */

		/**
		 * Assign new content to container
		 * Replacing its current contents, modifying its size accordingly
		 * the new contents are elements constructed from each of the elements in the range between first and last\
		 *   in the same order
		 * @reference https://www.cplusplus.com/reference/list/list/assign/
		 * @tparam InputIterator
		 * @param first (begin of the Iterator)
		 * @param last (end of the Iterator)
		 */
		void assign(iterator first, iterator last)
		{
			clear();
			while (first != last)
			{
				this->push_back(*first);
				first++;
			}
		}

		/**
		 * Assign new content to container
		 * Replacing its current contents, modifying its size accordingly
		 * the new contents are elements constructed from each of the elements in the range between first and last\
		 *   in the same order
		 * @reference https://www.cplusplus.com/reference/list/list/assign/
		 * @tparam InputIterator
		 * @param first (begin of the Iterator)
		 * @param last (end of the Iterator)
		 */
		void assign(const_iterator first, const_iterator last)
		{
			clear();
			while (first != last)
			{
				this->push_back(*first);
				first++;
			}
		}

		/**
		 * Assign new content to container
		 * the new contents are n elements, each initialized to a copy of val
		 * @reference https://www.cplusplus.com/reference/list/list/assign/
		 * @param n (number of elements)
		 * @param val (value to copy into container)
		 */
		void assign(size_type n, const value_type &val)
		{
			this->clear();
			for (size_type i = 0; i < n; ++i)
				push_back(val);
		}

		/**
		 * Insert element at beginning
		 * Inserts a new element at the beginning of the list, right before its current first element
		 * The content of val is copied (or moved) to the inserted element
		 * @reference https://www.cplusplus.com/reference/list/list/push_front/
		 * @param val (Value to be copied)
		 */
		void push_front(const value_type &val)
		{
			Node<value_type> *node = new Node<value_type>(NULL, val, NULL);
			if (this->empty()) this->c_end->insert_before(node);
			else this->c_begin->insert_before(node);
			this->c_begin = node;
			this->c_len++;
		}

		/**
		 * Add element at the end
		 * Adds a new element at the end of the list container, after its current last element
		 * @reference https://www.cplusplus.com/reference/list/list/push_back/
		 * @param val (Value to be copied)
		 */
		void push_back(const value_type &val)
		{
			Node<value_type> *node = new Node<value_type>(NULL, val, NULL);
			this->c_end->insert_before(node);
			if (this->empty()) this->c_begin = node;
			this->c_len++;
		}

		/**
		 * Delete first element
		 * Removes the first element in the list container, effectively reducing its size by one
		 * @reference https://www.cplusplus.com/reference/list/list/pop_front/
		 */
		void pop_front()
		{
			if (this->empty()) return;
			else if (this->size() == 1)
			{
				delete this->c_begin;
				this->c_begin     = this->c_end;
				this->c_end->prev = NULL;
				this->c_len--;
			}
			else
			{
				Node<value_type> *new_first_node = this->c_begin->next;
				this->c_begin->remove();
				delete this->c_begin;
				this->c_begin = new_first_node;
				this->c_len--;
			}
		}

		/**
		 * Delete last element
		 * Removes the last element in the list container, effectively reducing the container size by one
		 * @reference https://www.cplusplus.com/reference/list/list/pop_back/
		 */
		void pop_back()
		{
			if (this->empty()) return;
			else if (this->size() == 1) this->pop_front();
			else
			{
				Node<value_type> *new_last_node = this->c_end->prev;
				this->c_end->remove();
				delete this->c_end;
				this->c_end                     = new_last_node;
				this->c_len--;
			}
		}

		/**
		 * Single Element
		 *
		 * Inserts elements at the specified location in the container
		 * Inserts a single element before the pos
		 * @reference https://www.cplusplus.com/reference/list/list/insert/
		 * @reference https://en.cppreference.com/w/cpp/container/list/insert
		 * @param position (Position in the container where the new elements are inserted)
		 * @param val (Value to be copied)
		 * @return iterator (An iterator that points to the first of the newly inserted elements)
		 */
		iterator insert(iterator position, const value_type &val)
		{
			if (position == this->begin())
			{
				this->push_front(val);
				return (this->begin());
			}
			else if (position == this->end())
			{
				this->push_back(val);
				return (this->end());
			}
			else
			{
				Node<value_type> *new_node = new Node<T>(NULL, val, NULL);
				position.get_node()->insert_before(new_node);
				this->c_len++;
				return (position.get_node()->prev);
			}
		}

		/**
		 * Fill
		 *
		 * Inserts elements at the specified location in the container
		 * Inserts count copies of the value before pos
		 * @reference https://www.cplusplus.com/reference/list/list/insert/
		 * @reference https://en.cppreference.com/w/cpp/container/list/insert
		 * @param position (Position in the container where the new elements are inserted)
		 * @param n (Number of elements to insert)
		 * @param val (Value to be copied)
		 */
		void insert(iterator position, size_type n, const value_type &val)
		{
			for (size_type i = 0; i < n; ++i)
				this->insert(position, val);
		}

		/**
		 * Range
		 *
		 * Inserts elements at the specified location in the container
		 * Inserts elements from range [first, last) before pos
		 * @reference https://www.cplusplus.com/reference/list/list/insert/
		 * @reference https://en.cppreference.com/w/cpp/container/list/insert
		 * @tparam InputIterator
		 * @param position (Position in the container where the new elements are inserted)
		 * @param first (Begin of the iterator)
		 * @param last (End of the iterator)
		 */
		void insert(iterator position, iterator first, iterator last)
		{
			for (; first != last; first++)
			{
				insert(position, *first);
			}
		}

		/**
		 * Erase elements
		 * Removes from the list container either a single element (position)
		 * @reference https://www.cplusplus.com/reference/list/list/erase/
		 * @param position (Iterator pointing to a single element to be removed from the list)
		 * @return iterator (An iterator pointing to the element that followed\
		 *   the last element erased by the function call)
		 */
		iterator erase(iterator position)
		{
			if (position == this->begin())
			{
				this->pop_front();
				return (this->begin());
			}
			else if (position == this->end())
			{
				this->pop_back();
				return (this->end());
			}
			else
			{
				Node<value_type> *node = position.get_node()->next;
				position.get_node()->remove();
				this->c_len--;
				delete position.get_node();
				return (iterator(node));
			}
		}

		/**
		 * Erase elements
		 * Removes from the list container a range of elements ([first,last))
		 * @param first (begin of the range)
		 * @param last (end of the range)
		 * @return iterator (An iterator pointing to the element that followed\
		 *   the last element erased by the function call)
		 */
		iterator erase(iterator first, iterator last)
		{
			while (first != last)
			{
				this->erase(first);
				first++;
			}
			return (first);
		}

		/**
		 * Swap content
		 * Exchanges the content of the container by the content of x, which is another list of the same type
		 * Sizes may differ
		 * @reference https://www.cplusplus.com/reference/list/list/swap/
		 * @param x (Another list container of the same type as this)
		 */
		void swap(list &x)
		{
			this->swap(this->c_len, x.c_len);
			this->swap(this->c_end, x.c_end);
			this->swap(this->c_begin, x.c_begin);
		}

		/**
		 * Change size
		 * Resizes the container so that it contains n elements
		 *
		 * If n is smaller than the current container size, the content is reduced to its first n elements
		 * If n is greater than the current container size, the content is expanded by inserting at the end\
		 *   as many elements as needed to reach a size of n. If val is specified,\
		 *   the new elements are initialized as copies of val, otherwise, they are value-initialized
		 *
		 * @reference https://www.cplusplus.com/reference/list/list/resize/
		 * @param n (New container size, expressed in number of elements)
		 * @param val (Object whose content is copied to the added elements in case that n\
		 *   is greater than the current container size)
		 */
		void resize(size_type n, value_type val = value_type())
		{
			if (n < this->size())
			{
				iterator       begin_remove = this->begin();
				for (size_type i            = 0; i < n; ++i)
					begin_remove++;
				this->erase(begin_remove, this->end());
			}
			else if (n > this->size()) insert(this->end(), n - this->size(), val);
		}

		/**
		 * Clear content
		 * Removes all elements from the list container (which are destroyed)
		 * Leaving the container with a size of 0
		 * @reference https://www.cplusplus.com/reference/list/list/clear/
		 */
		void clear()
		{
			if (!this->empty())
				this->erase(this->begin(), this->end());
			bounds();
		}

		/*
		 * Operations
		 */

		/**
		 * Entire list
		 *
		 * Transfer elements from list to list
		 * Transfers all the elements of x into the container
		 * @reference https://www.cplusplus.com/reference/list/list/splice/
		 * @param position (Position within the container where the elements of x are inserted)
		 * @param x (A list object of the same type)
		 */
		void splice(iterator position, list &x)
		{
			this->splice(position, x, x.begin(), x.end());
		}

		/**
		 * Single Element
		 *
		 * Transfer elements from list to list
		 * transfers only the element pointed by i from x into the container
		 * @reference https://www.cplusplus.com/reference/list/list/splice/
		 * @param position (Position within the container where the elements of x are inserted)
		 * @param x (A list object of the same type)
		 * @param i (Iterator to an element in x)
		 */
		void splice(iterator position, list &x, iterator i)
		{
			this->insert(position, *i);
			x.erase(i);
		}

		/**
		 * Element range
		 *
		 * Transfer elements from list to list
		 * transfers the range [first,last) from x into the container
		 * @reference https://www.cplusplus.com/reference/list/list/splice/
		 * @param position (Position within the container where the elements of x are inserted)
		 * @param x (A list object of the same type)
		 * @param first (Start of the range)
		 * @param last (End of the range)
		 */
		void splice(iterator position, list &x, iterator first, iterator last)
		{
			insert(position, first, last);
			x.erase(first, last);
			if (first == x.begin() && last == x.end())
				x.clear();
		}

		/**
		 * Remove elements with specific value
		 * Removes from the container all the elements that compare equal to val
		 * @reference https://www.cplusplus.com/reference/list/list/remove/
		 * @param val (Value of the elements to be removed)
		 */
		void remove(const value_type &val)
		{
			iterator first = this->begin();
			while (first != this->end())
			{
				if (*first == val)
					this->erase(first);
				first++;
			}
		}

		/**
		 * Remove elements fulfilling condition
		 * Removes from the container all the elements for which Predicate pred returns true
		 * @reference https://www.cplusplus.com/reference/list/list/remove_if/
		 * @tparam Predicate
		 * @param pred (Unary predicate that, taking a value of the same type as those contained\
		 *   in the forward_list object, returns true for those values to be removed from the container,\
		 *   and false for those remaining.)
		 */
		template<class Predicate>
		void remove_if(Predicate pred)
		{
			iterator begin = this->begin();
			while (begin != this->end())
			{
				if (pred(*begin))
					this->erase(begin);
				begin++;
			}
		}

		/**
		 * Remove duplicated values
		 * Removes all but the first element from every consecutive group of equal elements in the container
		 * @reference https://www.cplusplus.com/reference/list/list/unique/
		 */
		void unique()
		{
			if (this->empty())
				return;
			iterator begin = this->begin();
			while (begin != this->end())
			{
				iterator current = begin;
				current++;
				while (current != this->end())
				{
					if (*current == *begin)
						this->erase(current);
					current++;
				}
				begin++;
			}
		}

		/**
		 * Remove duplicated values
		 * Takes as argument a specific comparison function that determine the "uniqueness" of an element
		 * @reference https://www.cplusplus.com/reference/list/list/unique/
		 * @tparam BinaryPredicate
		 * @param binary_pred (Binary predicate that, taking two values of the same type than those\
		 *   contained in the list, returns true to remove the element passed as first argument from\
		 *   the container, and false otherwise)
		 */
		template<class BinaryPredicate>
		void unique(BinaryPredicate binary_pred)
		{
			if (this->empty())
				return;
			iterator begin = this->begin();
			while (begin != this->end())
			{
				iterator current = begin;
				current++;
				while (current != this->end())
				{
					if (binary_pred(*begin, *current))
						this->erase(current);
					current++;
				}
				begin++;
			}
		}

		/**
		 * Merge sorted lists
		 *
		 * Merges x into the list by transferring all of its elements at their respective ordered\
		 *   positions into the container
		 * This effectively removes all the elements in x (which becomes empty), and inserts them into\
		 *   their ordered position within container (which expands in size by the number of elements transferred)
		 *
		 * Consider that both of the lists are sorted.
		 *
		 * @note The function does nothing if (&x == this)
		 * @reference https://www.cplusplus.com/reference/list/list/merge/
		 * @param x (A list object of the same type)
		 */
		void merge(list &x)
		{
			if (&x == this || x.empty())
				return;
			this->insert(this->begin(), x.begin(), x.end());
			this->sort();
			x.clear();
		}

		/**
		 * Merge sorted lists
		 *
		 * Merges x into the list by transferring all of its elements at their respective ordered\
		 *   positions into the container
		 * This effectively removes all the elements in x (which becomes empty), and inserts them into\
		 *   their ordered position within container (which expands in size by the number of elements transferred)
		 *
		 * Take a specific predicate (comp) to perform the comparison operation between elements
		 *
		 * @note The function does nothing if (&x == this)
		 * @reference https://www.cplusplus.com/reference/list/list/merge/
		 * @tparam Compare
		 * @param x (A list object of the same type)
		 * @param comp (Binary predicate that, taking two values of the same type than those contained\
		 *   in the list, returns true if the first argument is considered to go before the second in\
		 *   the strict weak ordering it defines, and false otherwise)
		 */
		template<class Compare>
		void merge(list &x, Compare comp)
		{
			if (&x == this || x.empty())
				return;
			this->insert(this->end(), x.begin(), x.end());
			this->sort(comp);
			x.clear();
		}

		/**
		 * Sort elements in container
		 * Sorts the elements in the list, altering their position within the container
		 *
		 * The sorting is performed by applying an algorithm that uses operator <
		 * @reference https://www.cplusplus.com/reference/list/list/sort/
		 */
		void sort()
		{
			this->sort(_sort_less_than<T>);
		}

		/**
		 * Sort elements in container
		 * Sorts the elements in the list, altering their position within the container
		 *
		 * The sorting is performed by applying an algorithm that uses comp to compare elements
		 * This comparison shall produce a strict weak ordering of the elements
		 * @reference https://www.cplusplus.com/reference/list/list/sort/
		 * @tparam Compare
		 * @param comp (Binary predicate that, taking two values of the same type of those contained\
		 *   in the list, returns true if the first argument goes before the second argument in the strict\
		 *   weak ordering it defines, and false otherwise)
		 */
		template<class Compare>
		void sort(Compare comp)
		{
			if (!this->empty())
			{
				for (size_type i = this->c_len; i > 1; i--)
				{
					for (size_type j = 0; j < i - 1; j++)
					{
						if (comp(this->_get(j + 1), this->_get(j)))
						{
							value_type tmp = this->_get(j + 1);
							this->_get(j + 1) = this->_get(j);
							this->_get(j)     = tmp;
						}
					}
				}
			}
		}

		/**
		 * Reverse the order of elements
		 * Reverses the order of the elements in the list container
		 * @reference https://www.cplusplus.com/reference/list/list/reverse/
		 */
		void reverse()
		{
			if (!this->empty())
			{
				size_type      len = this->c_len - 1;
				for (size_type i   = 0; i < len; i++)
				{
					value_type tmp  = this->_get(i);
					this->_get(i)   = this->_get(len);
					this->_get(len) = tmp;
					len--;
				}
			}
		}
	};

	/*
	 * Relational operators
	 */

	template<class T>
	bool operator==(list<T> &lhs, list<T> &rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		typename list<T>::iterator begin_lhs = lhs.begin();
		typename list<T>::iterator begin_rhs = rhs.begin();
		while (begin_lhs != lhs.end() && begin_rhs != rhs.end())
		{
			if (*begin_lhs != *begin_rhs)
				return (false);
			begin_lhs++;
			begin_rhs++;
		}
		return (true);
	}

	template<class T>
	bool operator!=(list<T> &lhs, list<T> &rhs)
	{
		return (!(lhs == rhs));
	}

	template<class T>
	bool operator<(list<T> &lhs, list<T> &rhs)
	{
		if (lhs == rhs)
			return (false);
		if (lhs.size() != rhs.size()) {
			return (lhs.size() < rhs.size());
		}
		typename list<T>::iterator begin_lhs = lhs.begin();
		typename list<T>::iterator begin_rhs = rhs.begin();
		while (begin_lhs != lhs.end() && begin_rhs != rhs.end())
		{
			if (*begin_lhs != *begin_rhs)
				return (*begin_lhs < *begin_rhs);
			begin_lhs++;
			begin_rhs++;
		}
		throw std::logic_error("wtf how did we come here ?");
	}

	template<class T>
	bool operator<=(list<T> &lhs, list<T> &rhs)
	{
		return ((lhs < rhs) || (lhs == rhs));
	}

	template<class T>
	bool operator>(list<T> &lhs, list<T> &rhs)
	{
		return (!(lhs <= rhs));
	}

	template<class T>
	bool operator>=(list<T> &lhs, list<T> &rhs)
	{
		return (!(lhs < rhs));
	}

	/**
	 * Exchanges the contents of two lists
	 * The contents of container x are exchanged with those of y.
	 * Both container objects must be of the same type
	 * @tparam T
	 * @param x (list container of the same type of y)
	 * @param y (list container of the same type of x)
	 */
	template<class T>
	void swap(list<T> &x, list<T> &y)
	{
		x.swap(y);
	}
}

#endif
