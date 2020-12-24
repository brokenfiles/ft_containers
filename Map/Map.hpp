#include <functional>
#include "../List/List.hpp"
#include "./BST.hpp"

namespace ft
{
	template<class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key, T> > >
	class map
	{
	public:
		typedef Key                                     key_type;
		typedef T                                       mapped_type;
		typedef Alloc                                   allocator_type;
		typedef Compare                                 key_compare;
		typedef Compare                                 value_compare;
		typedef BST<key_type, mapped_type,
				key_compare>                            bst_type;
		typedef typename bst_type::value_type           value_type;
		typedef value_type                              &reference;
		typedef const value_type                        &const_reference;
		typedef value_type                              *pointer;
		typedef const value_type                        *const_pointer;
		typedef typename bst_type::Iterator             iterator;
		typedef typename bst_type::ConstIterator        const_iterator;
		typedef typename bst_type::ReverseIterator      reverse_iterator;
		typedef typename bst_type::ConstReverseIterator const_reverse_iterator;
		typedef typename bst_type::Node                 node_type;
		typedef typename bst_type::Node                 *node_pointer;
		typedef ptrdiff_t                               difference_type;
		typedef size_t                                  size_type;

	private:
		key_compare    _compare;
		bst_type       _bst;
		allocator_type _allocator;

		template<typename S>
		void swap_t (S *t1, S *t2)
		{
			S tmp = *t1;
			*t1 = *t2;
			*t2 = tmp;
		}

	public:

		/**
		 * Empty map constructor
		 *
		 * Constructs an empty container, with no elements.
		 * @param comp Binary predicate that, taking two element keys as argument, returns true if the first argument
		 *   goes before the second argument in the strict weak ordering it defines, and false otherwise.
		 * @param alloc Allocator object. The container keeps and uses an internal copy of this allocator.
		 */
		explicit map (const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
		{
			this->_allocator = alloc;
			this->_bst       = bst_type();
			this->_compare   = comp;
		}

		/**
		 * Range map constructor
		 *
		 * Constructs a container with as many elements as the range [first,last), with each element constructed from its
		 * corresponding element in that range.
		 * @tparam InputIterator Input iterators to the initial and final positions in a range.
		 * @param first begin of the range
		 * @param last end of the range
		 * @param comp Binary predicate that, taking two element keys as argument, returns true if the first argument
		 *   goes before the second argument in the strict weak ordering it defines, and false otherwise.
		 * @param alloc Allocator object. The container keeps and uses an internal copy of this allocator.
		 */
		template<class InputIterator>
		map (InputIterator first, InputIterator last, const key_compare &comp = key_compare(),
			 const allocator_type &alloc = allocator_type())
		{
			this->_allocator = alloc;
			this->_bst       = bst_type();
			this->_compare   = comp;
			while (first != last)
			{
				this->insert(*first);
				first++;
			}
		}

		/**
		 * Copy map constructor
		 *
		 * Constructs a container with a copy of each of the elements in x.
		 * @param x Another map object of the same type
		 */
		map (const map &x)
		{
			this->_compare = x._compare;
			_bst.copyFrom(x._bst);
		}

		/**
		 * map destructor
		 *
		 * Destroys the container object.
		 */
		~map ()
		{
			_bst.clear_tree();
		}

		/**
		 * Assigns new contents to the container, replacing its current content.
		 *
		 * @param x A map object of the same type
		 * @return *this
		 */
		map &operator= (const map &x)
		{
			_bst.clear_tree();
			this->_bst = x._bst;
			return (*this);
		}

		/*
		 * Iterators
		 */

		iterator begin ()
		{ return (iterator(_bst.begin(), _bst.root())); }

		iterator end ()
		{ return (iterator(_bst.end(), _bst.root())); }

		const_iterator begin () const
		{ return (const_iterator(_bst.begin(), _bst.root())); }

		const_iterator end () const
		{ return (const_iterator(_bst.end(), _bst.root())); }

		reverse_iterator rbegin ()
		{ return (reverse_iterator(_bst.end()->_parent, _bst.root())); }

		reverse_iterator rend ()
		{
			if (_bst.getBegin() == NULL)
			{
				return (reverse_iterator(NULL, _bst.getRoot()));
			}
			return (reverse_iterator(_bst.begin()->_left, _bst.root()));
		}

		const_reverse_iterator rbegin () const
		{ return (const_reverse_iterator(_bst.end()->_left, _bst.root())); }

		const_reverse_iterator rend () const
		{
			if (_bst.getBegin() == NULL)
			{
				return (const_reverse_iterator(NULL, _bst.getRoot()));
			}
			return (const_reverse_iterator(_bst.begin()->_left, _bst.root()));
		}

		/*
		 * Capacity
		 */

		/**
		 * Test whether container is empty
		 *
		 * This function does not modify the container in any way. To clear the content of a map container, see map::clear.
		 *
		 * @return whether the map container is empty (i.e. whether its size is 0).
		 */
		bool empty () const
		{
			return (_bst.getLen() == 0);
		}

		/**
		 * Return container size
		 *
		 * @return the number of elements in the map container.
		 */
		size_type size () const
		{
			return (_bst.size());
		}

		/**
		 * Return maximum size
		 *
		 * This is the maximum potential size the container can reach due to known system or library implementation limitations
		 *
		 * @return the maximum number of elements that the map container can hold.
		 */
		size_type max_size () const
		{
			return (this->_allocator.max_size());
		}

		/**
		 * Access element
		 *
		 * If k matches the key of an element in the container, the function returns a reference to its mapped value.
		 * If k does not match the key of any element in the container, the function inserts a new element with that
		 *   key and returns a reference to its mapped value
		 *
		 * @param k
		 * @return
		 */
		mapped_type &operator[] (const key_type &k)
		{
			node_pointer found = _bst.find_by_key(k);
			if (found != NULL)
			{
				return (found->_content.second);
			}
			else
			{
				node_pointer inserted_node = _bst.insert(std::make_pair(k, mapped_type()));
				return (inserted_node->_content.second);
			}
		}

		/*
		 * Modifiers
		 */

		/**
		 * Insert elements
		 *
		 * Extends the container by inserting new elements, effectively increasing the container size by the
		 * number of elements inserted.
		 * @param val
		 * @return
		 */
		std::pair<iterator, bool> insert (const value_type &val)
		{
			node_pointer found = _bst.find_by_key(val.first);
			if (found != NULL)
			{
				return (std::make_pair(iterator(found, _bst.root()), false));
			}
			node_pointer new_node = _bst.insert(val);
			return (std::make_pair(iterator(new_node, _bst.root()), true));
		}

		/**
		 * Insert elements
		 *
		 * Extends the container by inserting new elements, effectively increasing the container size by the
		 * number of elements inserted.
		 * @param val
		 * @return
		 */
		iterator insert (iterator position, const value_type &val)
		{
			(void) position;
			node_pointer found = _bst.find_by_key(val.first);
			if (found != NULL)
			{
				return (iterator(found, _bst.root()));
			}
			node_pointer new_node = _bst.insert(val);
			return (iterator(new_node, _bst.root()));
		}

		/**
		 * Insert elements
		 *
		 * Extends the container by inserting new elements, effectively increasing the container size by the number
		 *   of elements inserted.
		 *
		 * @tparam InputIterator Iterators specifying a range of elements
		 * @param first begin of the range
		 * @param last end of the range
		 */
		template<class InputIterator>
		void insert (InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				this->insert(*first);
				first++;
			}
		}

		/**
		 * Erase elements
		 *
		 * Removes from the map container either a single element or a range of elements ([first,last)).
		 * This effectively reduces the container size by the number of elements removed
		 *
		 * @param position Iterator pointing to a single element to be removed from the map
		 */
		void erase (iterator position)
		{
			node_pointer found = _bst.find_by_key(position->first);
			if (found != NULL)
			{
				_bst.erase_from_key(position->first);
			}
		}

		/**
		 * Erase elements
		 *
		 * Removes from the map container either a single element or a range of elements ([first,last)).
		 * This effectively reduces the container size by the number of elements removed
		 *
		 * @param k Key of the element to be removed from the map.
		 * @return the number of elements erased
		 */
		size_type erase (const key_type &k)
		{
			node_pointer found = _bst.find_by_key(k);
			if (found != NULL)
			{
				_bst.erase_from_key(k);
			}
			return (found != NULL ? 1 : 0);
		}

		/**
		 * Erase elements
		 *
		 * Removes from the map container either a single element or a range of elements ([first,last)).
		 * This effectively reduces the container size by the number of elements removed
		 *
		 * @param first begin of the range
		 * @param last end of the range
		 */
		void erase (iterator first, iterator last)
		{
			if (first == this->begin() && last == this->end())
			{
				// just clear in this case
				this->clear();
			}
			else
			{
				while (first != last)
				{
					_bst.erase_from_key((first++)->first);
				}
			}
		}

		/**
		 * Swap content
		 *
		 * Exchanges the content of the container by the content of x, which is another map of the same type.
		 * Sizes may differ.
		 *
		 * @param x Another map container of the same type as this
		 */
		void swap (map &x)
		{
			this->swap_t(&this->_bst, &x._bst);
			this->swap_t(&this->_compare, &x._compare);
		}

		/**
		 * Clear content
		 *
		 * Removes all elements from the map container (which are destroyed)
		 * @reference https://www.cplusplus.com/reference/map/map/clear/
		 */
		void clear ()
		{
			_bst.clear_tree();
		}

		/**
		 * Return key comparison object
		 *
		 * Returns a copy of the comparison object used by the container to compare keys.
		 *
		 * @return The comparison object
		 */
		key_compare key_comp () const
		{
			return (this->_compare);
		}

		/**
		 * Return value comparison object
		 *
		 * Returns a comparison object that can be used to compare two elements to get whether the key of the first
		 *   one goes before the second.
		 *
		 * @return The comparison object for element values.
		 */
		value_compare value_comp () const
		{
			return (this->_compare);
		}

		/**
		 * Get iterator to element
		 *
		 * Searches the container for an element with a key equivalent to k and returns an iterator to it if found,
		 *   otherwise it returns an iterator to map::end
		 *
		 * @param k Key to be searched for.
		 * @return An iterator to the element, if an element with specified key is found, or map::end otherwise.
		 */
		iterator find (const key_type &k)
		{
			node_type *found = _bst.find_by_key(k);
			if (found)
			{
				return (iterator(found, _bst.root()));
			}
			return (iterator(_bst.end(), _bst.root()));
		}

		/**
		 * Get iterator to element
		 *
		 * Searches the container for an element with a key equivalent to k and returns an iterator to it if found,
		 *   otherwise it returns an iterator to map::end
		 *
		 * @param k Key to be searched for.
		 * @return An iterator to the element, if an element with specified key is found, or map::end otherwise.
		 */
		const_iterator find (const key_type &k) const
		{
			node_type *found = _bst.find_by_key(k);
			if (found)
			{
				return (const_iterator(found, this->_bst.root()));
			}
			return (const_iterator(this->_bst.end(), this->_bst.root()));
		}

		/**
		 * Count elements with a specific key
		 *
		 * Searches the container for elements with a key equivalent to k and returns the number of matches.
		 * Because all elements in a map container are unique, the function can only return 1 (if the element is found)
		 *   or zero (otherwise).
		 *
		 * @param k Key to search for.
		 * @return 1 if the container contains an element whose key is equivalent to k, or zero otherwise.
		 */
		size_type count (const key_type &k) const
		{
			return (find(k) != this->end() ? 1 : 0);
		}

		/**
		 * Return iterator to upper bound
		 *
		 * The function uses its internal comparison object (key_comp) to determine this, returning an iterator to
		 *   the first element for which key_comp(k,element_key) would return true.
		 *
		 * @param key Key to search for.
		 * @return an iterator pointing to the first element in the container whose key is considered to go after k
		 */
		iterator upper_bound (const Key &key)
		{
			for (iterator it = begin(); it != end(); it++)
			{
				if (_compare(key, it->first))
				{
					return (it);
				}
			}
			return (this->end());
		}

		/**
		 * Return iterator to upper bound
		 *
		 * The function uses its internal comparison object (key_comp) to determine this, returning an iterator to
		 *   the first element for which key_comp(k,element_key) would return true.
		 *
		 * @param key Key to search for.
		 * @return an iterator pointing to the first element in the container whose key is considered to go after k
		 */
		const_iterator upper_bound (const Key &key) const
		{
			for (iterator it = begin(); it != end(); it++)
			{
				if (_compare(key, it->first))
				{
					return (it);
				}
			}
			return (this->end());
		}

		/**
		 * Return iterator to lower bound
		 *
		 * The function uses its internal comparison object (key_comp) to determine this, returning an iterator
		 *   to the first element for which key_comp(element_key,k) would return false
		 *
		 * @param key Key to search for.
		 * @return an iterator pointing to the first element in the container whose key is not considered to go before k
		 */
		iterator lower_bound (const Key &key)
		{

			for (iterator it = begin(); it != end(); it++)
			{
				if (!_compare(it->first, key))
					return (it);
			}
			return (this->end());
		}

		/**
		 * Return iterator to lower bound
		 *
		 * The function uses its internal comparison object (key_comp) to determine this, returning an iterator
		 *   to the first element for which key_comp(element_key,k) would return false
		 *
		 * @param key Key to search for.
		 * @return an iterator pointing to the first element in the container whose key is not considered to go before k
		 */
		const_iterator lower_bound (const Key &key) const
		{

			for (iterator it = begin(); it != end(); it++)
			{
				if (!_compare(it->first, key))
					return (it);
			}
			return (this->end());
		}

		/**
		 * Get range of equal elements
		 *
		 * Returns the bounds of a range that includes all the elements in the container which
		 *   have a key equivalent to k.
		 *
		 * @param k Key to search for.
		 * @return a pair, whose member pair::first is the lower bound of the range
		 */
		std::pair<iterator, iterator> equal_range (const key_type &k)
		{
			return (std::make_pair(lower_bound(k), upper_bound(k)));
		}

		/**
		 * Get range of equal elements
		 *
		 * Returns the bounds of a range that includes all the elements in the container which
		 *   have a key equivalent to k.
		 *
		 * @param k Key to search for.
		 * @return a pair, whose member pair::first is the lower bound of the range
		 */
		std::pair<const_iterator, const_iterator> equal_range (const key_type &k) const
		{
			return (std::make_pair(lower_bound(k), upper_bound(k)));
		}
	};

	template<class Key, class T, class Compare>
	bool operator== (map<Key, T, Compare> &lhs,
					 map<Key, T, Compare> &rhs)
	{
		if (lhs.size() != rhs.size())
		{
			return (false);
		}
		if (lhs.size() > 0)
		{
			typedef typename map<Key, T, Compare>::iterator iterator;
			iterator                                        rhs_begin = rhs.begin();
			for (iterator                                   lhs_begin = lhs.begin();
				 lhs_begin != lhs.end(); lhs_begin++)
			{
				if (lhs_begin->first != rhs_begin->first || lhs_begin->second != rhs_begin->second)
				{
					return (false);
				}
				rhs_begin++;
			}
		}
		return (true);
	}

	template<class Key, class T, class Compare>
	bool operator!= (map<Key, T, Compare> &lhs,
					 map<Key, T, Compare> &rhs)
	{
		return !(lhs == rhs);
	}

	template<class Key, class T, class Compare>
	bool operator< (map<Key, T, Compare> &lhs,
					map<Key, T, Compare> &rhs)
	{
		if (rhs.empty() || lhs.empty())
		{
			return (lhs.size() < rhs.size());
		}
		typedef typename map<Key, T, Compare>::iterator iterator;
		iterator                                        rhs_begin = rhs.begin();
		for (iterator                                   lhs_begin = lhs.begin();
			 lhs_begin != lhs.end(); lhs_begin++)
		{
			if (lhs_begin->first != rhs_begin->first || lhs_begin->second != rhs_begin->second)
			{
				return (*lhs_begin < *rhs_begin);
			}
			rhs_begin++;
		}
		return (lhs.size() < rhs.size());
	}

	template<class Key, class T, class Compare>
	bool operator> (map<Key, T, Compare> &lhs,
					map<Key, T, Compare> &rhs)
	{
		return (rhs < lhs);
	}

	template<class Key, class T, class Compare>
	bool operator<= (map<Key, T, Compare> &lhs,
					 map<Key, T, Compare> &rhs)
	{
		return !(rhs < lhs);
	}

	template<class Key, class T, class Compare>
	bool operator>= (map<Key, T, Compare> &lhs,
					 map<Key, T, Compare> &rhs)
	{
		return !(lhs < rhs);
	}


}