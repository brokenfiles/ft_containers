#include <functional>
#include "../List/List.hpp"
#include "./BST.hpp"

namespace ft
{
	template<class Key, class T, class Compare = std::less<Key> >
	class Map
	{
	public:
		typedef Key                                                 key_type;
		typedef T                                                   mapped_type;
		typedef std::pair<const key_type, mapped_type>              value_type;
		typedef Compare                                             key_compare;
		typedef Compare                                             value_compare;
		typedef value_type                                          &reference;
		typedef const value_type                                    &const_reference;
		typedef value_type                                          *pointer;
		typedef const value_type                                    *const_pointer;
		typedef BST<key_type, mapped_type, key_compare>             bst_type;
		typedef BST<const key_type, const mapped_type, key_compare> const_bst_type;
		typedef typename bst_type::Iterator                         iterator;
		typedef typename const_bst_type::Iterator                   const_iterator;
		typedef typename bst_type::Iterator                         reverse_iterator;
		typedef typename const_bst_type::Iterator                   const_reverse_iterator;
		typedef typename bst_type::Node                             node_type;
		typedef typename bst_type::Node                             *node_pointer;
		typedef ptrdiff_t                                           difference_type;
		typedef size_t                                              size_type;

	private:
		key_compare _compare;
		bst_type    _bst;

		template<typename S>
		void swap(S *t1, S *t2)
		{
			S tmp = *t1;
			*t1 = *t2;
			*t2 = tmp;
		}

	public:
		/**
		 * Empty Map constructor
		 * @param comp
		 */
		explicit Map(const key_compare &comp = key_compare())
		{
			this->_bst     = bst_type();
			this->_compare = comp;
		}

		/**
		 * Range Map constructor
		 *
		 * Constructs a container with as many elements as the range [first,last), with each element constructed from its
		 * corresponding element in that range.
		 * @tparam InputIterator
		 * @param first
		 * @param last
		 * @param comp
		 */
		template<class InputIterator>
		Map(InputIterator first, InputIterator last, const key_compare &comp = key_compare())
		{
			this->_bst     = bst_type();
			this->_compare = comp;
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
		 * @param x
		 */
		Map(const Map &x)
		{
			this->_bst     = bst_type();
			this->_compare = x._compare;
			_bst.copyFrom(x._bst);
		}

		/**
		 * Map destructor
		 */
		~Map()
		{
			_bst.clear_tree();
		}

		/**
		 * Assigns new contents to the container, replacing its current content.
		 *
		 * @param x
		 * @return
		 */
		Map &operator=(const Map &x)
		{
			_bst.clear_tree();
			this->_bst = x._bst;
			return (*this);
		}

		/*
		 * Iterators
		 */

		iterator begin()
		{
			return (iterator(_bst.begin(), _bst.root()));
		}

		iterator end()
		{
			return (iterator(_bst.end(), _bst.root()));
		}

		const_iterator begin() const
		{
			return (const_iterator(_bst.begin(), _bst.root()));
		}

		const_iterator end() const
		{
			return (const_iterator(_bst.end(), _bst.root()));
		}

		iterator rbegin()
		{
			return (reverse_iterator(_bst.begin(), _bst.root()));
		}

		iterator rend()
		{
			return (reverse_iterator(_bst.end(), _bst.root()));
		}

		const_iterator rbegin() const
		{
			return (const_reverse_iterator(_bst.begin(), _bst.root()));
		}

		const_iterator rend() const
		{
			return (const_reverse_iterator(_bst.end(), _bst.root()));
		}

		/*
		 * Capacity
		 */

		/**
		 * Test whether container is empty
		 *
		 * @return whether the map container is empty (i.e. whether its size is 0).
		 */
		bool empty() const
		{
			return (_bst.empty());
		}

		/**
		 * Return container size
		 *
		 * @return the number of elements in the map container.
		 */
		size_type size() const
		{
			return (_bst.size());
		}

		/**
		 * Return maximum size
		 *
		 * @return the maximum number of elements that the map container can hold.
		 */
		size_type max_size() const
		{
			return (std::min((size_type) std::numeric_limits<difference_type>::max(),
							 std::numeric_limits<size_type>::max() / (sizeof(node_type) + sizeof(pointer))));
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
		mapped_type &operator[](const key_type &k)
		{
			node_pointer found = _bst.find_by_key(NULL, k);
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
		std::pair<iterator, bool> insert(const value_type &val)
		{
			node_pointer found = _bst.find_by_pair(_bst.root(), val);
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
		iterator insert(iterator position, const value_type &val)
		{
			node_pointer found = _bst.find_by_pair(_bst.root(), val);
			if (found != NULL)
			{
				return (std::make_pair(iterator(found, _bst.root()), false));
			}
			node_pointer new_node = _bst.insert(position._node, val);
			return (iterator(new_node, _bst.root()));
		}

		template<class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				this->insert(*first);
				first++;
			}
		}

		void erase(iterator position)
		{
			node_pointer found = _bst.find_by_pair(position._node->_content);
			if (found != NULL)
			{
				_bst.delete_by_pair(position._node->_content);
			}
		}

		size_type erase(const key_type &k)
		{
			node_pointer found = _bst.find_by_key(k);
			if (found != NULL)
			{
				_bst.delete_by_pair(found->_content);
			}
			return (found != NULL ? 1 : 0);
		}

		void erase(iterator first, iterator last)
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
					first = iterator(_bst.delete_by_pair(first._node->_content), first._root);
				}
			}
		}

		void swap(Map &x)
		{
			this->swap(this->_bst, x._bst);
			this->swap(this->_compare, x._compare);
		}

		void clear()
		{
			_bst.clear_tree();
		}

		key_compare key_comp() const
		{
			return (this->_compare);
		}

		value_compare value_comp() const
		{
			return (this->_compare);
		}

		iterator find(const key_type &k)
		{
			node_type *found = _bst.find_by_key(k);
			if (found)
			{
				return (iterator(found, this->root()));
			}
			return (iterator(this->end(), this->root()));
		}

		const_iterator find(const key_type &k) const
		{
			node_type *found = _bst.find_by_key(k);
			if (found)
			{
				return (const_iterator(found, this->root()));
			}
			return (const_iterator(this->end(), this->root()));
		}

		size_type count(const key_type &k) const
		{
			node_type *found = _bst.find_by_key(k);
			return (found != NULL ? 1 : 0);
		}

		iterator upper_bound(const Key &key)
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

		iterator lower_bound(const Key &key)
		{

			for (iterator it = begin(); it != end(); it++)
			{
				if (!_compare(it->first, key))
					return (it);
			}
			return (this->end());
		}

		std::pair<iterator, iterator> equal_range(const key_type &k)
		{
			return (std::pair<iterator, iterator>(this->lower_bound(k), this->upper_bound(k)));
		}

		std::pair<const_iterator, const_iterator> equal_range(const key_type &k) const
		{
			return (std::pair<const_iterator, const_iterator>(this->lower_bound(k), this->upper_bound(k)));
		}


	};
}