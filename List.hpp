
#ifndef FT_CONTAINERS_LIST_HPP
#define FT_CONTAINERS_LIST_HPP

#include <iostream>

namespace ft
{
	template <typename T>
	class ListIterator
	{

	};

	template <typename T>
	class ReverseListIterator
	{

	};

	template<class T>
	class List
	{
	public:
		typedef T								value_type;

		typedef size_t							size_type;
		typedef std::ptrdiff_t					difference_type;

		typedef T&								reference;
		typedef const T&						const_reference;
		typedef T*								pointer;
		typedef const T*						const_pointer;

		typedef ListIterator<T>					iterator;
		typedef ListIterator<const T>			const_iterator;
		typedef ReverseListIterator<T>			reverse_iterator;
		typedef ReverseListIterator<const T>	const_reverse_iterator;

	public:
		/*
		 * Colpien
		 */

		/**
		 * Class destructor
		 * This destroys all container elements
		 * deallocates all the storage capacity allocated by the list container using its allocator.
		 * @param NULL
		 */
		virtual ~List()
		{
			// TODO : destructor implementation
		}

		/**
		 * empty container constructor (default)
		 */
		List()
		{
			// TODO : empty container constructor implementation
		}

		/**
		 * fill constructor
		 * constructs a container with n elements (each element is a copy of val)
		 * @param n number of elements
		 * @param val value to insert
		 */
		List(size_type n, const value_type &val = value_type())
		{
			// TODO : fill constructor implementation
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
		List(InputIterator first, InputIterator last)
		{
			// TODO : range constructor implementation
		}

		/**
		 * copy constructor
		 * Constructs a container with a copy of each of the elements in x in the same order
		 * @param x other List to copy
		 */
		List(const List& x)
		{
			// TODO : copy constructor implementation
		}

		/*
		 * Assignation
		 */

		/**
		 * Assignation = function
		 * Assigns new contents to the container
		 * replacing its current contents
		 * modifying its size accordingly
		 * @param x other List to copy
		 * @return current instance
		 */
		List& operator= (const List& x)
		{
			return (*this);
		}

		/*
		 * Iterators
		 */

		iterator begin() {}
		const_iterator begin() const {}

		iterator end() {}
		const_iterator end() const {}

		reverse_iterator rbegin() {}
		const_reverse_iterator rbegin() const {}

		reverse_iterator rend() {}
		const_reverse_iterator rend() const {}

		/*
		 * -- Public functions --
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
			// TODO : empty implementation
		}

		/**
		 * @return size_type (The number of elements in the container)
		 */
		size_type size() const
		{
			// TODO : size implementation
		}

		/**
		 * used to know the maximum potential size the container can reach\
		 *   due to known system or library implementation limitations
		 * @return size_type (The maximum number of elements the object can hold as content)
		 */
		size_type max_size() const
		{
			// TODO : max_size implementation
		}

		/*
		 * Element access
		 */

		/**
		 * @return reference (a reference to the first element in the list container)
		 */
		reference front()
		{
			// TODO : front implementation
		}

		/**
		 * @return const_reference (a reference to the first element in the list container)
		 */
		const_reference front() const
		{
			// TODO : front const implementation
		}

		/**
		 * @return reference (a reference to the last element in the list container)
		 */
		reference back()
		{
			// TODO : back const implementation
		}

		/**
		 * @return const_reference (a reference to the last element in the list container)
		 */
		const_reference back() const
		{
			// TODO : back const implementation
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
		template <class InputIterator>
		void assign (InputIterator first, InputIterator last)
		{
			// TODO : range assign implemenetation
		}

		/**
		 * Assign new content to container
		 * the new contents are n elements, each initialized to a copy of val
		 * @reference https://www.cplusplus.com/reference/list/list/assign/
		 * @param n (number of elements)
		 * @param val (value to copy into container)
		 */
		void assign (size_type n, const value_type& val)
		{
			// TODO : fill assign implementation
		}

		/**
		 * Insert element at beginning
		 * Inserts a new element at the beginning of the list, right before its current first element
		 * The content of val is copied (or moved) to the inserted element
		 * @reference https://www.cplusplus.com/reference/list/list/push_front/
		 * @param val (Value to be copied)
		 */
		void push_front (const value_type& val)
		{
			// TODO : push_front implementation
		}

		/**
		 * Delete first element
		 * Removes the first element in the list container, effectively reducing its size by one
		 * @reference https://www.cplusplus.com/reference/list/list/pop_front/
		 */
		void pop_front()
		{
			// TODO : pop_front implementation
		}

		/**
		 * Delete last element
		 * Removes the last element in the list container, effectively reducing the container size by one
		 * @reference https://www.cplusplus.com/reference/list/list/pop_back/
		 */
		void pop_back()
		{
			// TODO : pop_back implementation
		}

		/**
		 * Add element at the end
		 * Adds a new element at the end of the list container, after its current last element
		 * @reference https://www.cplusplus.com/reference/list/list/push_back/
		 * @param val (Value to be copied)
		 */
		void push_back (const value_type& val)
		{
			// TODO : push_back implementation
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
		iterator insert (iterator position, const value_type& val)
		{
			// TODO : single element insert implementation
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
		void insert (iterator position, size_type n, const value_type& val)
		{
			// TODO : fill insert implementation
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
		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last)
		{
			// TODO : range insert implementation
		}

		/**
		 * Erase elements
		 * Removes from the list container either a single element (position)
		 * @reference https://www.cplusplus.com/reference/list/list/erase/
		 * @param position (Iterator pointing to a single element to be removed from the list)
		 * @return iterator (An iterator pointing to the element that followed\
		 *   the last element erased by the function call)
		 */
		iterator erase (iterator position)
		{
			// TODO : single erase implementation
		}

		/**
		 * Erase elements
		 * Removes from the list container a range of elements ([first,last))
		 * @param first (begin of the range)
		 * @param last (end of the range)
		 * @return iterator (An iterator pointing to the element that followed\
		 *   the last element erased by the function call)
		 */
		iterator erase (iterator first, iterator last)
		{
			// TODO : range erase implementation
		}

		/**
		 * Swap content
		 * Exchanges the content of the container by the content of x, which is another list of the same type
		 * Sizes may differ
		 * @reference https://www.cplusplus.com/reference/list/list/swap/
		 * @param x (Another list container of the same type as this)
		 */
		void swap (List& x)
		{
			// TODO : swap implementation
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
		void resize (size_type n, value_type val = value_type())
		{
			// TODO : resize implementation
		}

		/**
		 * Clear content
		 * Removes all elements from the list container (which are destroyed)
		 * Leaving the container with a size of 0
		 * @reference https://www.cplusplus.com/reference/list/list/clear/
		 */
		void clear()
		{
			// TODO : clear implementation
		}

		/*
		 * Operations
		 */


	};
}

#endif
