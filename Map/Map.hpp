#include <functional>
#include "Less.hpp"
#include "../List/List.hpp"

namespace ft
{
	template<class Key, class T, class Compare = ft::Less<Key> >
	class Map
	{
	public:
		typedef Key									key_type;
		typedef T									mapped_type;
		typedef std::pair<key_type, mapped_type>	value_type;
		typedef Compare								key_compare;
		typedef value_type&							reference;
		typedef const value_type&					cont_reference;
		typedef value_type*							pointer;
		typedef const value_type*					const_pointer;
		/* iterators */
		/* TODO make iterators */
		typedef ptrdiff_t							difference_type;
		typedef size_t								size_type;

	private:
		ft::List<key_type> c_keys;
		ft::List<mapped_type> c_mapped;
		key_compare _comp;

	public:
		Map (const key_compare& comp = key_compare())
		{
			this->_comp = comp;
		}

		template <class InputIterator>
		Map (InputIterator first, InputIterator last,
			 const key_compare& comp = key_compare())
		{
			this->_comp = comp;
		}

		Map (const Map& x)
		{
			*this = x;
		}


	};
}