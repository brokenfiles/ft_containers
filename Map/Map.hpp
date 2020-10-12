#include <functional>
#include "Less.hpp"
#include "../List/List.hpp"
#include "./BinarySearchTree.hpp"

namespace ft
{
	template<class Key, class T, class Compare = std::less<Key> >
	class Map
	{
	public:
		typedef Key											key_type;
		typedef T											mapped_type;
		typedef std::pair<key_type, mapped_type>			value_type;
		typedef Compare										key_compare;
		typedef value_type&									reference;
		typedef const value_type&							cont_reference;
		typedef value_type*									pointer;
		typedef const value_type*							const_pointer;


		typedef 			BST<Key,
				T,
				key_compare>					tree_type;
		typedef typename	tree_type::Elem 					elem_type;
		typedef 			elem_type*							elem_pointer;
		/* iterators */
		typedef typename BST<Key, T, Compare>::BSTIterator	iterator;
		typedef typename BST<Key const, const T,
									Compare>::BSTIterator	const_iterator;
		typedef typename BST<Key, T,
							Compare>::ReverseBSTIterator	reverse_iterator;
		typedef typename BST<Key const, const T,
							Compare>::ReverseBSTIterator	const_reverse_iterator;



		/* TODO make iterators */
		typedef ptrdiff_t									difference_type;
		typedef size_t										size_type;

	private:
		BST<Key, T, Compare>								c_tree;

	public:

		iterator begin() { return (iterator(this->c_tree.begin(), this->c_tree.m_root )); }
		iterator end() { return (iterator(this->c_tree.end(), this->c_tree.m_root )); }

		const_iterator begin() const { return (const_iterator(this->c_tree.begin(), this->c_tree.m_root )); }
		const_iterator end() const { return (const_iterator(this->c_tree.end(), this->c_tree.m_root )); }

		reverse_iterator rbegin() { return (reverse_iterator(this->c_tree.end(), this->c_tree.m_root )); }
		const_reverse_iterator rbegin() const { return (const_reverse_iterator(this->c_tree.end(), this->c_tree.m_root )); }

		reverse_iterator rend() { return (reverse_iterator(this->c_tree.begin(), this->c_tree.m_root )); }
		const_reverse_iterator rend() const { return (const_reverse_iterator(this->c_tree.begin(), this->c_tree.m_root )); }

		Map ()
		{ }

		Map (iterator first, iterator last)
		{
			while (first != last)
			{
				this->insert(*first);
				first++;
			}
		}

		Map (const Map& x)
		{
			this->c_tree.copyBST(x.c_tree);
		}

		virtual ~Map()
		{
			this->c_tree.clear();
		}

		Map &operator=(const Map& rhs)
		{
			this->clear();
			this->c_tree = rhs.c_tree;
			return (*this);
		}

		mapped_type& operator[] (const key_type& k)
		{
			elem_pointer element = this->c_tree.find(k);
			if (element)
			{
				return (element->m_pair.second);
			}
			else
			{
				elem_pointer new_element = this->c_tree.insert(std::make_pair(k, mapped_type()));
				return (new_element->m_pair.second);
			}
		}

		bool empty() const
		{
			return (this->size() == 0);
		}

		size_type size() const
		{
			return (this->c_tree.size());
		}

		size_t max_size() const {
			return (std::min((size_type) std::numeric_limits<difference_type>::max(),
							 std::numeric_limits<size_type>::max() / (sizeof(elem_type) + sizeof(pointer))));
		}

		std::pair<iterator, bool> insert (const value_type& val)
		{
			elem_pointer found = this->c_tree.find_pair(val);
			if (found)
			{
				return (std::make_pair(iterator(found, this->c_tree.m_root), 0));
			}
			else
			{
				elem_pointer element = this->c_tree.insert(val);
				return (std::make_pair(iterator(element, this->c_tree.m_root), 1));
			}
		}

		iterator insert (iterator position, const value_type& val)
		{
			elem_pointer element = position.m_elem;
			elem_pointer new_element = this->c_tree.insertPairAtHint(element, val);
			return (iterator(new_element, this->c_tree.m_root));
		}

		void insert (iterator first, iterator last)
		{
			while (first != last)
			{
				this->insert(*first);
				first++;
			}
		}

		void erase (iterator position)
		{
			this->c_tree.deleteElem(position.m_elem);
		}

		size_type erase (const key_type& k)
		{
			return (this->c_tree.erase(k));
		}

		void erase (iterator first, iterator last)
		{
			while (first != last)
			{
				first = this->erase(*first);
			}
		}

		void swap (Map& x)
		{
			this->c_tree.swap(x.c_tree);
		}

		void clear()
		{
			this->erase(this->begin(), this->end());
		}

		iterator find (const key_type& k)
		{
			elem_pointer found = this->c_tree.find(k);
			if (found)
			{
				return (iterator(found, this->c_tree.m_root));
			}
			return (this->end());
		}

		const_iterator find (const key_type& k) const
		{
			elem_pointer found = this->c_tree.find(k);
			if (found)
			{
				return (const_iterator(found, this->c_tree.m_root));
			}
			return (this->end());
		}

		size_type count (const key_type& k) const
		{
			elem_pointer found = this->c_tree.find(k);
			return (found ? 1 : 0);
		}



	};
}