#include <iostream>
#include <cmath>
#include "../utils.hpp"

namespace ft
{
	template<typename T>
	class VectorIterator
	{
	public:
		typedef T							value_type;
		typedef T&							reference;
		typedef T*							pointer;
		typedef std::ptrdiff_t				difference_type;

	private:
		pointer	ptr_content;

	public:

		VectorIterator(void)
		{ ptr_content = NULL; }

		VectorIterator(pointer ptr_content)
		{ this->ptr_content = ptr_content; }

		VectorIterator(const VectorIterator &x)
		{ this->ptr_content = x.ptr_content; }

		~VectorIterator()
		{}

		VectorIterator<value_type> &operator=(const VectorIterator<value_type>& rhs)
		{
			this->ptr_content = rhs.ptr_content;
			return (*this);
		}

		/*
		 * Arithmetic Operators
		 */

		VectorIterator<T> &operator++()
		{
			this->ptr_content++;
			return (*this);
		}

		VectorIterator<T> operator++(int)
		{
			VectorIterator<T> it = *this;
			this->ptr_content++;
			return (it);
		}

		VectorIterator<T> &operator--()
		{
			this->ptr_content--;
			return (*this);
		}

		VectorIterator<T> operator--(int)
		{
			VectorIterator<T> it = *this;
			this->ptr_content--;
			return (it);
		}

		VectorIterator<T> operator+(difference_type n)
		{
			return (VectorIterator<value_type>(this->ptr_content + n));
		}

		VectorIterator<T> operator+(VectorIterator<value_type> x)
		{

			return (this->ptr_content + x.ptr_content);
		}

		VectorIterator<T> operator-(difference_type n)
		{
			return (VectorIterator<value_type>(this->ptr_content - n));
		}

		difference_type operator-(VectorIterator<value_type> x)
		{
			return (this->ptr_content - x.ptr_content);
		}

		/*
		 * Member and pointer operators
		 */

		reference operator[](difference_type x)
		{
			return (*(this->ptr_content + x));
		}

		reference operator*()
		{
			return (*(this->ptr_content));
		}

		/*
		 * Compound assignment operators
		 */

		VectorIterator<T> &operator+=(difference_type n)
		{
			this->ptr_content += n;
			return (*this);
		}

		VectorIterator<T> &operator-=(difference_type n)
		{
			this->ptr_content -= n;
			return (*this);
		}

		/*
		 * Equality operators
		 */

		bool operator==(const VectorIterator<T>& rhs)
		{
			return (this->ptr_content == rhs.ptr_content);
		}

		bool operator!=(const VectorIterator<T>& rhs)
		{
			return (this->ptr_content != rhs.ptr_content);
		}
	};

	template<class T>
	class ReverseVectorIterator
	{
	public:
		typedef T							value_type;
		typedef T&							reference;
		typedef T*							pointer;
		typedef std::ptrdiff_t				difference_type;

	private:
		pointer	ptr_content;

	public:

		ReverseVectorIterator(void)
		{ ptr_content = NULL; }

		ReverseVectorIterator(pointer ptr_content)
		{ this->ptr_content = ptr_content; }

		ReverseVectorIterator(const ReverseVectorIterator &x)
		{ this->ptr_content = x.ptr_content; }

		~ReverseVectorIterator()
		{}

		ReverseVectorIterator<value_type> &operator=(const ReverseVectorIterator<value_type>& rhs)
		{
			this->ptr_content = rhs.ptr_content;
			return (*this);
		}

		/*
		 * Arithmetic Operators
		 */

		ReverseVectorIterator<T> &operator++()
		{
			this->ptr_content--;
			return (*this);
		}

		ReverseVectorIterator<T> operator++(int)
		{
			ReverseVectorIterator<T> it = *this;
			this->ptr_content--;
			return (it);
		}

		ReverseVectorIterator<T> &operator--()
		{
			this->ptr_content++;
			return (*this);
		}

		ReverseVectorIterator<T> operator--(int)
		{
			ReverseVectorIterator<T> it = *this;
			this->ptr_content++;
			return (it);
		}

		ReverseVectorIterator<T> operator+(difference_type n)
		{
			return (ReverseVectorIterator<value_type>(this->ptr_content - n));
		}

		ReverseVectorIterator<T> operator+(ReverseVectorIterator<value_type> x)
		{
			return (ReverseVectorIterator<value_type>(this->ptr_content - x.ptr_content));
		}

		ReverseVectorIterator<T> operator-(difference_type n)
		{
			return (ReverseVectorIterator<value_type>(this->ptr_content - n));
		}

		difference_type operator-(ReverseVectorIterator<value_type> x)
		{
			return (this->ptr_content - x.ptr_content);
		}

		/*
		 * Member and pointer operators
		 */

		reference operator[](difference_type x)
		{
			return (*(this->ptr_content + x));
		}

		reference operator*()
		{
			return (*(this->ptr_content));
		}

		/*
		 * Compound assignment operators
		 */

		ReverseVectorIterator<T> &operator+=(difference_type n)
		{
			this->ptr_content -= n;
			return (*this);
		}

		ReverseVectorIterator<T> &operator-=(difference_type n)
		{
			this->ptr_content += n;
			return (*this);
		}

		/*
		 * Equality operators
		 */

		bool operator==(const ReverseVectorIterator<T>& rhs)
		{
			return (this->ptr_content == rhs.ptr_content);
		}

		bool operator!=(const ReverseVectorIterator<T>& rhs)
		{
			return (this->ptr_content != rhs.ptr_content);
		}
	};

	template<class T, class Allocator = std::allocator<T> >
	class Vector {
	public:
		typedef T									value_type;
		typedef Allocator							allocator_type;

		typedef T&									reference;
		typedef const T&							const_reference;
		typedef T*									pointer;
		typedef const T*							const_pointer;

		typedef VectorIterator<T>					iterator;
		typedef VectorIterator<const T>				const_iterator;
		typedef ReverseVectorIterator<T>			reverse_iterator;
		typedef ReverseVectorIterator<const T>		const_reverse_iterator;

		typedef ptrdiff_t							difference_type;
		typedef size_t								size_type;

	protected:
		T*				c_container;
		size_type		c_len;
		size_type		c_capacity;
		allocator_type	allocator;

	private:
		size_type get_new_capacity(size_type requested_capacity)
		{
			size_type new_cap = 0;
			size_type power = 0;
			while (new_cap < requested_capacity)
			 { new_cap = pow(2, power++); }
			return (new_cap);
		}

		void realloc(size_type previous_capacity)
		{
			T* new_container;
			new_container = this->allocator.allocate(this->c_capacity);
			for (size_type i = 0; i < this->size(); ++i)
			{
				this->allocator.construct(&new_container[i], this->c_container[i]);
				this->allocator.destroy(&this->c_container[i]);
			}
			this->allocator.deallocate(this->c_container, previous_capacity);
			this->c_container = new_container;
		}

	public:

		/**
		 * empty container constructor (default constructor)
		 * Constructs an empty container, with no elements.
		 *
		 * @reference https://www.cplusplus.com/reference/vector/vector/vector/
		 * @param alloc Allocator
		 */
		Vector (const allocator_type& alloc = allocator_type())
		{
			this->c_len = 0;
			this->c_capacity = 0;
			this->c_container = NULL;
			this->c_container = allocator.allocate(this->capacity());
		}

		/**
		 * fill constructor
		 * Constructs a container with n elements. Each element is a copy of val.
		 *
		 * @reference https://www.cplusplus.com/reference/vector/vector/vector/
		 * @param n number of values to be added
		 * @param val the value to copy n times in the container
		 * @param alloc allocator
		 */
		Vector (size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type())
		{
			this->c_len = 0;
			this->c_capacity = n;
			this->c_container = NULL;
			this->c_container = allocator.allocate(this->capacity());
			this->assign(n, val);
		}

		/**
		 * range constructor
		 * Constructs a container with as many elements as the range [first,last), with each element\
		 *   constructed from its corresponding element in that range, in the same order.
		 *
		 * @reference https://www.cplusplus.com/reference/vector/vector/vector/
		 * @param first iterator (begin of the range)
		 * @param last iterator (end of the range)
		 * @param alloc allocator
		 */
		Vector (iterator first, iterator last,
		const allocator_type& alloc = allocator_type())
		{
			this->c_len = 0;
			this->c_capacity = this->get_new_capacity(last - first);
			this->c_container = NULL;
			this->c_container = allocator.allocate(this->capacity());
			this->assign(first, last);
		}

		/**
		 * copy constructor
		 * Constructs a container with a copy of each of the elements in x, in the same order.
		 *
		 * @reference https://www.cplusplus.com/reference/vector/vector/vector/
		 * @param x other vector
		 */
		Vector (const Vector& x)
		{
			this->c_len = 0;
			this->c_capacity = x.capacity();
			this->c_container = NULL;
			this->c_container = allocator.allocate(this->capacity());
			this->assign(x.begin(), x.end());
		}

		/**
		 * Vector destructor
		 * Destroys the container object.
		 *
		 * This destroys all container elements, and deallocates all the storage capacity\
		 *   allocated by the vector using its allocator.
		 */
		~Vector()
		{
			this->allocator.deallocate(this->c_container, this->capacity());
		}

		/**
		 * Assign content
		 * Assigns new contents to the container, replacing its current contents and modifying its size
		 *
		 * @reference https://www.cplusplus.com/reference/vector/vector/operator=/
		 * @param x another Vector object to copy
		 * @return this instance
		 */
		Vector& operator= (const Vector& x)
		{
			this->assign(x.begin(), x.end());
			return (*this);
		}

		/*
		 * Iterators
		 */

		iterator begin() { return (iterator(&this->at(0))); }
		const_iterator begin() const { return (const_iterator(&this->at(0))); }

		iterator end() { return (iterator(&this->at(this->size()))); }
		const_iterator end() const { return (const_iterator(&this->at(this->size()))); }

		reverse_iterator rbegin() { return (reverse_iterator(&this->at(0))); }
		const_reverse_iterator rbegin() const { return (const_reverse_iterator(&this->at(0))); }

		reverse_iterator rend() { return (reverse_iterator(&this->at(this->size()))); }
		const_reverse_iterator rend() const { return (reverse_iterator(&this->at(this->size()))); }

		/*
		 * Capacity
		 */

		/**
		 * Return size
		 * Returns the number of elements in the vector
		 *
		 * @reference https://www.cplusplus.com/reference/vector/vector/size/
		 * @return container's size
		 */
		size_type size() const
		{
			return (this->c_len);
		}

		/**
		 * Return maximum size
		 * Returns the maximum number of elements that the vector can hold
		 *
		 * @reference https://www.cplusplus.com/reference/vector/vector/max_size/
		 * @return the maximum number of elements
		 */
		size_type max_size() const
		{
			return std::numeric_limits<std::size_t>::max() / (sizeof(ft::Vector<value_type>) - sizeof(pointer));
		}

		/**
		 * Change size
		 * Resizes the container so that it contains n elements.
		 *
		 * If n is smaller than the current container size, the content is reduced to its first n elements\
		 *   removing those beyond (and destroying them).
		 * If n is greater than the current container size, the content is expanded by inserting at the end\
		 *   as many elements as needed to reach a size of n.
		 * If n is also greater than the current container capacity, an automatic reallocation of the allocated\
		 *   storage space takes place.
		 *
		 * @reference https://www.cplusplus.com/reference/vector/vector/resize/
		 * @param n new container size
		 * @param val new value of the elements
		 */
		void resize (size_type n, value_type val = value_type())
		{
			if ((int)n < 0) { return ; }
			if (n < this->size())
			 { this->erase(this->begin() + n, this->end()); }
			else if (n > this->size())
			 { this->insert(this->end(), n - this->size(), val); }
		}

		/**
		 * Return size of allocated storage capacity
		 * Returns the size of the storage space currently allocated for the vector, expressed in terms of elements
		 *
		 * This capacity is not necessarily equal to the vector size. It can be equal or greater, with the extra\
		 *   space allowing to accommodate for growth without the need to reallocate on each insertion
		 * @reference https://www.cplusplus.com/reference/vector/vector/capacity/
		 * @return the size of currently allocated storage capacity
		 */
		size_type capacity() const
		{
			return (this->c_capacity);
		}

		/**
		 * Test wether vector is empty
		 * Returns whether the vector is empty
		 *
		 * @reference https://www.cplusplus.com/reference/vector/vector/empty/
		 * @return true if the container size is 0, false otherwise
		 */
		bool empty() const
		{
			return (this->size() == 0);
		}

		/**
		 * Request a change in capacity
		 * Requests that the vector capacity be at least enough to contain n elements.
		 *
		 * If n is greater than the current vector capacity, the function causes the container\
		 *   to reallocate its storage increasing its capacity to n (or greater)
		 * In all other cases, the function call does not cause a reallocation and the vector capacity is not affected
		 * This function has no effect on the vector size and cannot alter its elements
		 *
		 * @reference https://www.cplusplus.com/reference/vector/vector/reserve/
		 * @param n the minimum capacity for the vector
		 */
		void reserve (size_type n)
		{
			if (n > this->capacity())
			{
				if (n > this->max_size())
					throw(std::length_error("new requested size is upper than the max size"));
				size_type previous_capacity = this->c_capacity;
				this->c_capacity = n;
				this->realloc(previous_capacity);
			}
		}

		/*
		 * Elements access
		 */

		/**
		 * Access element
		 * Returns a reference to the element at position n in the vector container
		 *
		 * @similar vector::at
		 * @reference https://www.cplusplus.com/reference/vector/vector/operator[]/
		 * @param n position of an element in the container
		 * @return the element at the specified position in the vector
		 */
		reference operator[] (size_type n)
		{
			return (this->at(n));
		}

		/**
		 * Access const element
		 * Returns a reference to the element at position n in the vector container
		 *
		 * @similar vector::at
		 * @reference https://www.cplusplus.com/reference/vector/vector/operator[]/
		 * @param n position of an element in the container
		 * @return the element at the specified position in the vector
		 */
		const_reference operator[] (size_type n) const
		{
			return (this->at(n));
		}

		/**
		 * Access element
		 * Returns a reference to the element at position n in the vector container
		 *
		 * @similar vector::operator[]
		 * @reference https://www.cplusplus.com/reference/vector/vector/at/
		 *
		 * @param n position of an element in the container
		 * @return the element at the specified position in the vector
		 */
		reference at (size_type n)
		{
			return (*(this->c_container + n));
		}

		/**
		 * Access const element
		 * Returns a reference to the element at position n in the vector container
		 *
		 * @similar vector::operator[]
		 * @reference https://www.cplusplus.com/reference/vector/vector/at/
		 * @param n position of an element in the container
		 * @return the element at the specified position in the vector
		 */
		const_reference at (size_type n) const
		{
			return (*(this->c_container + n));
		}

		/**
		 * Access first element
		 * Returns a reference to the first element in the vector
		 *
		 * @similar vector::at(0)
		 * @reference https://www.cplusplus.com/reference/vector/vector/front/
		 * @return the element at the begin
		 */
		reference front()
		{
			return (this->at(0));
		}

		/**
		 * Access const first element
		 * Returns a reference to the first element in the vector
		 *
		 * @similar vector::at(0)
		 * @reference https://www.cplusplus.com/reference/vector/vector/front/
		 * @return the element at the begin
		 */
		const_reference front() const
		{
			return (this->at(0));
		}

		/**
		 * Access last element
		 * Returns a reference to the first element in the vector
		 *
		 * @similar vector::at(last_index)
		 * @reference https://www.cplusplus.com/reference/vector/vector/end/
		 * @return the element at the end
		 */
		reference back()
		{
			return (this->at(this->size() - 1));
		}

		/**
		 * Access const last element
		 * Returns a reference to the first element in the vector
		 *
		 * @similar vector::at(last_index)
		 * @reference https://www.cplusplus.com/reference/vector/vector/end/
		 * @return the element at the end
		 */
		const_reference back() const
		{
			return (this->at(this->size() - 1));
		}

		/**
		 * Assign vector content (Range)
		 * Assigns new contents to the vector, replacing its current contents, and modifying\
		 *   its size accordingly.
		 *
		 * @reference https://www.cplusplus.com/reference/vector/vector/assign/
		 * @param first begin of the range
		 * @param last end of the range
		 */
		void assign (iterator first, iterator last)
		{
			this->clear();
			while (first != last)
			{
				push_back(*first);
				first++;
			}
		}

		/**
		 * Assign const vector content (Range)
		 * Assigns new contents to the vector, replacing its current contents, and modifying\
		 *   its size accordingly.
		 *
		 * @reference https://www.cplusplus.com/reference/vector/vector/assign/
		 * @param first begin of the range
		 * @param last end of the range
		 */
		void assign (const_iterator first, const_iterator last)
		{
			this->clear();
			while (first != last)
			{
				push_back(*first);
				first++;
			}
		}

		/**
		 * Assign const vector content (Fill)
		 * Assigns new contents to the vector, replacing its current contents, and modifying\
		 *   its size accordingly.
		 *
		 * @reference https://www.cplusplus.com/reference/vector/vector/assign/
		 * @param n new size of the container
		 * @param val value to fill container with
		 */
		void assign (size_type n, const value_type& val)
		{
			this->clear();
			for (size_type i = 0; i < n; ++i)
			 { push_back(val); }
		}

		/**
		 * Add element at the end
		 * Adds a new element at the end of the vector, after its current last element
		 *
		 * @reference https://www.cplusplus.com/reference/vector/vector/push_back/
		 * @param val value to be copied
		 */
		void push_back (const value_type& val)
		{
			// make request to reserve some space
			if (this->size() + 1 > this->capacity())
			 { this->reserve(get_new_capacity(this->size() + 1)); }
			// pushwing value
			this->c_container[this->size()] = val;
			this->c_len ++;
		}

		/**
		 * Delete last element
		 * Removes the last element in the vector, reducing the container size by one
		 * @reference https://www.cplusplus.com/reference/vector/vector/pop_back/
		 */
		void pop_back()
		{
			this->erase(this->end());
		}

		/**
		 * Insert elements (single element version)
		 * The vector is extended by inserting the new elements before the element at the specified position
		 *
		 * This causes an automatic reallocation of the allocated storage space if -and only if-\
		 *   the new vector size surpasses the current vector capacity.
		 *
		 * @reference https://www.cplusplus.com/reference/vector/vector/insert/
		 * @param position in the vector where the new elements are inserted
		 * @param val value to be copied
		 * @return an iterator that points to the first of the newly inserted element
		 */
		iterator insert (iterator position, const value_type& val)
		{
			insert(position, 1, val);
			return (position + 1);
		}

		/**
		 * Insert elements (fill version)
		 * The vector is extended by inserting the new elements before the element at the specified position
		 *
		 * This causes an automatic reallocation of the allocated storage space if -and only if-\
		 *   the new vector size surpasses the current vector capacity.
		 *
		 * @reference https://www.cplusplus.com/reference/vector/vector/insert/
		 * @param position in the vector where the new elements are inserted
		 * @param n number of elements to insert
		 * @param val value to be copied
		 */
		void insert (iterator position, size_type n, const value_type& val)
		{
			if (n <= 0) { return ; }
			difference_type _position_index = position - this->begin();
			this->reserve(this->get_new_capacity(this->size() + n));
			for (size_type index = (this->size() + n); index >= n; --index)
			 { this->c_container[index] = this->c_container[index - n]; }
			this->c_len += n;
			for (size_type index = _position_index; index < _position_index + n; ++index)
			 { this->c_container[index] = val; }
		}

		/**
		 * Insert elements (range version)
		 * The vector is extended by inserting the new elements before the element at the specified position
		 *
		 * This causes an automatic reallocation of the allocated storage space if -and only if-\
		 *   the new vector size surpasses the current vector capacity.
		 *
		 * @reference https://www.cplusplus.com/reference/vector/vector/insert/
		 * @param position position in the vector where the new elements are inserted
		 * @param first begin of element's range
		 * @param last end of element's range
		 */
		void insert (iterator position, iterator first, iterator last)
		{
			difference_type _position_index = position - this->begin();
			difference_type _elements = last - first;
			if (_elements <= 0) { return ; }
			this->reserve(this->get_new_capacity(this->size() + _elements));
			for (size_type i = (this->size() + _elements); i >= _elements; --i)
			 { this->allocator.construct(&this->c_container[i], this->c_container[i - _elements]); }
			this->c_len += _elements;
			for (size_type i = _position_index; i < (_position_index + _elements); ++i)
			 { this->c_container[i] = *(first++); }
		}

		/**
		 * Insert elements (const range version)
		 * The vector is extended by inserting the new elements before the element at the specified position
		 *
		 * This causes an automatic reallocation of the allocated storage space if -and only if-\
		 *   the new vector size surpasses the current vector capacity.
		 *
		 * @reference https://www.cplusplus.com/reference/vector/vector/insert/
		 * @param position position in the vector where the new elements are inserted
		 * @param first begin of element's range
		 * @param last end of element's range
		 */
		void insert (iterator position, const_iterator first, const_iterator last)
		{
			difference_type _position_index = position - this->begin();
			difference_type _elements = last - first;
			if (_elements <= 0) { return ; }
			this->reserve(this->get_new_capacity(this->size() + _elements));
			for (size_type i = (this->size() + _elements); i >= _elements; --i)
			{ this->allocator.construct(&this->c_container[i], this->c_container[i - _elements]); }
			this->c_len += _elements;
			for (size_type i = _position_index; i < (_position_index + _elements); ++i)
			{ this->c_container[i] = *(first++); }
		}

		/**
		 * Erase elements
		 * Remove from the vector a single element
		 *
		 * This effectively reduces the container size by the number of elements removed, which are destroyed.
		 *
		 * @reference https://www.cplusplus.com/reference/vector/vector/erase/
		 * @param position iterator pointing to a single element to be removed
		 * @return an iterator pointing to the new location of the last element erased
		 */
		iterator erase (iterator position)
		{
			difference_type _pos_index = position - this->begin() - 1;
			for (size_type index = _pos_index; index < this->size() - 1; index ++)
			 { this->c_container[index] = this->c_container[index + 1]; }
			this->c_len --;
			return (position + 1);
		}

		/**
		 * Erase elements
		 * Remove from the vector a range of elements
		 *
		 * This effectively reduces the container size by the number of elements removed, which are destroyed.
		 *
		 * @reference https://www.cplusplus.com/reference/vector/vector/erase/
		 * @param first begin of the range
		 * @param last end of the range
		 * @return an iterator pointing to the new location of the last element erased
		 */
		iterator erase (iterator first, iterator last)
		{
			difference_type _first_index = first - this->begin();
			difference_type _last_index  = last  - this->begin();
			difference_type _elements    = last - first;

			for ( ; _first_index < _last_index; ++_first_index)
			 { this->c_container[_first_index] = this->c_container[_first_index + _elements]; }
			this->c_len -= _elements;
			return (iterator(this->c_container + _first_index));
		}

		/**
		 * Swap content
		 *
		 * Exchanges the content of the container by the content of x (vector of a same type)
		 * @reference https://www.cplusplus.com/reference/vector/vector/swap/
		 * @param x another vector
		 */
		void swap (Vector& x)
		{
			ft::swap(this->c_len, x.c_len);
			ft::swap(this->c_container, x.c_container);
			ft::swap(this->c_capacity, x.c_capacity);
		}

		/**
		 * Clear content
		 * Removes all elements from the vector, leaving the container with a size of 0
		 * A reallocation is not guaranteed to happen
		 * @reference https://www.cplusplus.com/reference/vector/vector/clear/
		 */
		void clear()
		{
			if (! this->empty())
				this->erase(this->begin(), this->end());
		}

		/*
		 * Getters
		 */

		/**
		 * Get allocator
		 * Returns a copy of the allocator object associated with the vector
		 * @return the allocator
		 */
		allocator_type get_allocator() const
		{
			return (this->allocator);
		}
	};

	// TODO implement relational operators
	template<class T>
	bool operator==(const Vector<T> &lhs, const Vector<T> &rhs)
	{
		if (lhs.size() != rhs.size())
		 { return (false); }
		for (typename Vector<T>::size_type i = 0; i < rhs.size(); ++i)
		{
			if (lhs[i] != rhs[i])
			 { return false; }
		}
		return (true);
	}

	template<class T>
	bool operator<(const Vector<T> &lhs, const Vector<T> &rhs)
	{
		if (lhs.size() < rhs.size())
		 { return true; }
		if (lhs.size() > rhs.size())
		 { return false; }
		for (typename Vector<T>::size_type i = 0; i < rhs.size(); ++i)
		{
			if (lhs[i] > rhs[i])
			 { return (false); }
		}
		return (true);
	}

	template<class T>
	bool operator!=(const Vector<T> &lhs, const Vector<T> &rhs)
	{
		return (!(lhs == rhs));
	}

	template<class T>
	bool operator>(const Vector<T> &lhs, const Vector<T> &rhs)
	{
		return (rhs < lhs);
	}

	template<class T>
	bool operator<=(const Vector<T> &lhs, const Vector<T> &rhs)
	{
		return (!(rhs < lhs));
	}

	template<class T>
	bool operator>=(const Vector<T> &lhs, const Vector<T> &rhs)
	{
		return (!(lhs < rhs));
	}

}
