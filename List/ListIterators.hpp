#ifndef LIST_ITERATORS_HPP
# define LIST_ITERATORS_HPP

# include <iostream>

namespace ft {

	template<typename T>
	struct Node
	{
		Node<T> *prev;
		T       content;
		Node<T> *next;

		/**
		 * Default constructor
		 * Initiate all values to NULL
		 */
		Node()
		{
			content = T();
			prev    = NULL;
			next    = NULL;
		}

		/**
		 * Fill Constructor
		 * Insert the node into others nodes
		 * @param prev (another Node with same type to put in previous node)
		 * @param content (content with T type)
		 * @param next (another Node with same type to put in next node)
		 */
		Node(Node<T> *prev, const T &content, Node<T> *next)
		{
			this->prev    = prev;
			this->content = content;
			this->next    = next;
		}

		/**
		 * Copy constructor
		 * @param node (another Node with same type to copy)
		 */
		Node(const Node<T> *node)
		{
			*this = node;
		}

		/**
		 * Assignation operator =
		 * Copy Node rhs into this Node
		 * @param rhs (another Node of the same type)
		 * @return Node (this instance)
		 */
		Node &operator=(const Node<T> &rhs)
		{
			this->next    = rhs.next;
			this->prev    = rhs.prev;
			this->content = rhs.content;
			return (*this);
		}

		/*
		 * Functions
		 */

		/**
		 * Adding another Node in front of this
		 * @param node (another node of the same type)
		 */
		void insert_before(Node<T> *n_node)
		{
			if (this->prev)
			{
				n_node->prev     = this->prev;
				this->prev->next = n_node;
			}
			this->prev   = n_node;
			n_node->next = this;
		}

		/**
		 * Remove this node from the chained list
		 */
		void remove()
		{
			if (this->next) this->next->prev = this->prev;
			if (this->prev) this->prev->next = this->next;
		}
	};

	template<typename T>
	class ConstListIterator;

	template<typename T>
	class ListIterator
	{

	private:
		Node<T>                *node;

	public:
		typedef T              value_type;
		typedef T              &reference;
		typedef T              *pointer;
		typedef std::ptrdiff_t difference_type;

		/*
		 * Constructors
		 */

		/**
		 * Default constructor
		 * Initiate nodes to NULL
		 */
		ListIterator()
		{
			node = NULL;
		}

		/**
		 * Constructor that takes other nodes
		 * Initiate nodes with the parameter
		 * @param node (other node, the same type)
		 */
		ListIterator(Node<T> *node)
		{
			this->node = node;
		}

		/**
		 * Copy constructor
		 * @param listIterator (other ListIterator, the same type)
		 */
		ListIterator(const ListIterator *listIterator)
		{
			*this = listIterator;
		}

		/**
		 * Assignation operator =
		 * Copy rhs to this
		 * @param rhs (other ListIterator, same type)
		 * @return this instance
		 */
		ListIterator<T> &operator=(const ListIterator<T> &rhs)
		{
			this->node = rhs.node;
			return (*this);
		}

		/*
		 * Getter
		 */

		Node<value_type> *get_node() const
		{ return this->node; }

		/*
		 * Operators
		 */

		ListIterator<T> &operator++()
		{
			node = node->next;
			return (*this);
		}

		ListIterator<T> &operator--()
		{
			node = node->prev;
			return (*this);
		}

		ListIterator<T> operator++(int)
		{
			ListIterator<T> tmp = (*this);
			node                = node->next;
			return (tmp);
		}

		ListIterator<T> operator--(int)
		{
			ListIterator<T> tmp = (*this);
			node                = node->prev;
			return (tmp);
		}

		ListIterator(const ConstListIterator<T> &x)
		{
			this->node = x.node;
		}

		ListIterator &operator=(const ConstListIterator<T> &x)
		{
			this->node = x.node;
			return (*this);
		}

		operator ConstListIterator<T>()
		{ return (ConstListIterator<T>(this->node)); }

		reference operator*() const
		{
			return (this->node->content);
		}

		bool operator==(const ListIterator<T> &rhs)
		{
			return (rhs.node->content == this->node->content
					&& rhs.node->next == this->node->next
					&& rhs.node->prev == this->node->prev);
		}

		bool operator!=(const ListIterator<T> &rhs)
		{
			return (rhs.node->content != this->node->content
					|| rhs.node->prev != this->node->prev
					|| rhs.node->next != this->node->next);
		}
	};
	template<typename T>
	class ConstListIterator
	{

	private:
		Node<T>                *node;

	public:
		typedef T              value_type;
		typedef const T        &reference;
		typedef const T        *pointer;
		typedef std::ptrdiff_t difference_type;

		/*
		 * Constructors
		 */

		/**
		 * Default constructor
		 * Initiate nodes to NULL
		 */
		ConstListIterator()
		{
			node = NULL;
		}

		/**
		 * Constructor that takes other nodes
		 * Initiate nodes with the parameter
		 * @param node (other node, the same type)
		 */
		ConstListIterator(Node<T> *node)
		{
			this->node = node;
		}

		/**
		 * Copy constructor
		 * @param listIterator (other ConstListIterator, the same type)
		 */
		ConstListIterator(const ConstListIterator *listIterator)
		{
			*this = listIterator;
		}

		/**
		 * Assignation operator =
		 * Copy rhs to this
		 * @param rhs (other ConstListIterator, same type)
		 * @return this instance
		 */
		ConstListIterator<T> &operator=(const ConstListIterator<T> &rhs)
		{
			this->node = rhs.node;
			return (*this);
		}

		/*
		 * Getter
		 */

		Node<value_type> *get_node() const
		{ return this->node; }

		/*
		 * Operators
		 */

		ConstListIterator<T> &operator++()
		{
			node = node->next;
			return (*this);
		}

		ConstListIterator<T> &operator--()
		{
			node = node->prev;
			return (*this);
		}

		ConstListIterator<T> operator++(int)
		{
			ConstListIterator<T> tmp = (*this);
			node                     = node->next;
			return (tmp);
		}

		ConstListIterator<T> operator--(int)
		{
			ConstListIterator<T> tmp = (*this);
			node                     = node->prev;
			return (tmp);
		}

		ConstListIterator(const ListIterator<T> &x)
		{
			this->node = x.node;
		}

		ConstListIterator &operator=(const ListIterator<T> &x)
		{
			this->node = x.node;
			return (*this);
		}

		operator ListIterator<T>()
		{ return (ListIterator<T>(this->node)); }

		reference operator*() const
		{
			return (this->node->content);
		}

		bool operator==(const ConstListIterator<T> &rhs)
		{
			return (rhs.node->content == this->node->content
					&& rhs.node->next == this->node->next
					&& rhs.node->prev == this->node->prev);
		}

		bool operator!=(const ConstListIterator<T> &rhs)
		{
			return (rhs.node->content != this->node->content
					|| rhs.node->prev != this->node->prev
					|| rhs.node->next != this->node->next);
		}
	};
	template<typename T>
	class ConstReverseListIterator;
	template<typename T>
	class ReverseListIterator
	{

	public:
		typedef T              value_type;
		typedef T              &reference;
		typedef T              *pointer;
		typedef std::ptrdiff_t difference_type;
		Node<T>                *node;

		/*
		 * Constructors
		 */

		/**
		 * Default constructor
		 * Initiate nodes to NULL
		 */
		ReverseListIterator()
		{
			node = NULL;
		}

		/**
		 * Constructor that takes other nodes
		 * Initiate nodes with the parameter
		 * @param node (other node, the same type)
		 */
		ReverseListIterator(Node<T> *node)
		{
			this->node = node;
		}

		/**
		 * Copy constructor
		 * @param listIterator (other ReverseListIterator, the same type)
		 */
		ReverseListIterator(const ReverseListIterator *listIterator)
		{
			*this = listIterator;
		}

		/**
		 * Assignation operator =
		 * Copy rhs to this
		 * @param rhs (other ReverseListIterator, same type)
		 * @return this instance
		 */
		ReverseListIterator<T> &operator=(const ReverseListIterator<T> &rhs)
		{
			this->node = rhs.node;
			return (*this);
		}

		/*
		 * Getter
		 */

		Node<value_type> *get_node() const
		{ return this->node; }

		/*
		 * Operators
		 */

		ReverseListIterator<T> &operator++()
		{
			node = node->prev;
			return (*this);
		}

		ReverseListIterator<T> &operator--()
		{
			node = node->next;
			return (*this);
		}

		ReverseListIterator<T> operator++(int)
		{
			ReverseListIterator<T> tmp = (*this);
			node                       = node->prev;
			return (tmp);
		}

		ReverseListIterator<T> operator--(int)
		{
			ReverseListIterator<T> tmp = (*this);
			node                       = node->next;
			return (tmp);
		}

		reference operator*() const
		{
			return (this->node->content);
		}

		ReverseListIterator(const ConstReverseListIterator<T> &x)
		{
			this->node = x.node;
		}

		ReverseListIterator &operator=(const ConstReverseListIterator<T> &x)
		{
			this->node = x.node;
			return (*this);
		}

//		operator ConstReverseListIterator<T>()
//		{ return (ReverseListIterator<T>(this->node)); }

		bool operator==(const ReverseListIterator<T> &rhs)
		{
			return (rhs.node->content == this->node->content
					&& rhs.node->next == this->node->next
					&& rhs.node->prev == this->node->prev);
		}

		bool operator!=(const ReverseListIterator<T> &rhs)
		{
			return (rhs.node->content != this->node->content
					|| rhs.node->prev != this->node->prev
					|| rhs.node->next != this->node->next);
		}
	};
	template<typename T>
	class ConstReverseListIterator
	{

	public:
		typedef T              value_type;
		typedef const T        &reference;
		typedef const T        *pointer;
		typedef std::ptrdiff_t difference_type;
		Node<T>                *node;

		/*
		 * Constructors
		 */

		/**
		 * Default constructor
		 * Initiate nodes to NULL
		 */
		ConstReverseListIterator()
		{
			node = NULL;
		}

		/**
		 * Constructor that takes other nodes
		 * Initiate nodes with the parameter
		 * @param node (other node, the same type)
		 */
		ConstReverseListIterator(Node<T> *node)
		{
			this->node = node;
		}

		/**
		 * Copy constructor
		 * @param listIterator (other ConstReverseListIterator, the same type)
		 */
		ConstReverseListIterator(const ConstReverseListIterator *listIterator)
		{
			*this = listIterator;
		}

		/**
		 * Assignation operator =
		 * Copy rhs to this
		 * @param rhs (other ConstReverseListIterator, same type)
		 * @return this instance
		 */
		ConstReverseListIterator<T> &operator=(const ConstReverseListIterator<T> &rhs)
		{
			this->node = rhs.node;
			return (*this);
		}

		/*
		 * Getter
		 */

		Node<value_type> *get_node() const
		{ return this->node; }

		/*
		 * Operators
		 */

		ConstReverseListIterator<T> &operator++()
		{
			node = node->prev;
			return (*this);
		}

		ConstReverseListIterator<T> &operator--()
		{
			node = node->next;
			return (*this);
		}

		ConstReverseListIterator<T> operator++(int)
		{
			ConstReverseListIterator<T> tmp = (*this);
			node                            = node->prev;
			return (tmp);
		}

		ConstReverseListIterator<T> operator--(int)
		{
			ConstReverseListIterator<T> tmp = (*this);
			node                            = node->next;
			return (tmp);
		}

		reference operator*() const
		{
			return (this->node->content);
		}

		ConstReverseListIterator(const ReverseListIterator<T> &x)
		{
			this->node = x.node;
		}

		ConstReverseListIterator &operator=(const ReverseListIterator<T> &x)
		{
			this->node = x.node;
			return (*this);
		}

		operator ReverseListIterator<T>()
		{ return (ConstReverseListIterator<T>(this->node)); }

		bool operator==(const ConstReverseListIterator<T> &rhs)
		{
			return (rhs.node->content == this->node->content
					&& rhs.node->next == this->node->next
					&& rhs.node->prev == this->node->prev);
		}

		bool operator!=(const ConstReverseListIterator<T> &rhs)
		{
			return (rhs.node->content != this->node->content
					|| rhs.node->prev != this->node->prev
					|| rhs.node->next != this->node->next);
		}
	};
}

#endif