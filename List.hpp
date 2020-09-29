
#ifndef FT_CONTAINERS_LIST_HPP
#define FT_CONTAINERS_LIST_HPP

#include <iostream>

namespace ft
{
	template<class T, class Alloc>
	class List
	{
	public:
		typedef T value_type;
		typedef Alloc allocator_type;
		/* Déclaration des tailles & différences */
		typedef size_t size_type;
		typedef std::ptrdiff_t difference_type;
		/* Déclaration des références */
		typedef T &reference;
		typedef const T &const_reference;
		/* Déclaration des pointeurs */
		typedef T *pointer;
		typedef const T *const_pointer;

		/* Déclaration des itérateurs */

	public:
		/* Classe colpienne */

		/**
		 * Default class constructor.
		 * Initiate the list class
		 * @param NULL
		 */
		List(void)
		{
			// TODO : tout initier à 0
		}

		/**
		 * Class destructor
		 * This destroys all container elements
		 * deallocates all the storage capacity allocated by the list container using its allocator.
		 * @param NULL
		 */
		virtual ~List()
		{
			// TODO : tout clear
		}

		/**
		 * empty container constructor (default)
		 * @param alloc allocator class
		 */
		List(const allocator_type &alloc = allocator_type())
		{
			// TODO : initier avec ce constructeur
		}

		/**
		 * fill constructor
		 * constructs a container with n elements (each element is a copy of val)
		 * @param n number of elements
		 * @param val value to insert
		 * @param alloc allocator
		 */
		List(size_type n, const value_type &val = value_type(),
			 const allocator_type &alloc = allocator_type())
		{
			// TODO : fill constructor
		}

		/**
		 * range constructor
		 * constructs a container with as many elements as the range (first, last)
		 * with each element constructed from its corresponding element in that range, in the same order
		 * @tparam InputIterator iterator class
		 * @param first first iterator (begin of the range)
		 * @param last last iterator (end of the range)
		 * @param alloc allocator
		 */
		template<class InputIterator>
		List(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type())
		{
			// TODO : range constructor
		}

		/**
		 * copy constructor
		 * Constructs a container with a copy of each of the elements in x in the same order
		 * @param x other List to copy
		 */
		List(const List& x)
		{

		}
	};
}

#endif
