#ifndef MAP_BINARY_TREE_HPP
# define MAP_BINARY_TREE_HPP

# include <iostream>

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key> >
	struct Node
	{
		typedef std::pair<Key, T>	pair_type;
		typedef struct node			node_type;

		pair_type			pair;
		node_type			*right;
		node_type			*left;
		node_type			*parent;

		Node(void)
		{
			this->pair   = pair_type();
			this->right  = NULL;
			this->left   = NULL;
			this->parent = NULL;
		}

		Node(pair_type other_pair)
		{
			this->pair   = other_pair;
			this->right  = NULL;
			this->left   = NULL;
			this->parent = NULL;
		}

		Node(pair_type other_pair, node_type *right, node_type *left, node_type *parent)
		{
			this->pair   = other_pair;
			this->right  = right;
			this->left   = left;
			this->parent = parent;
		}

		Node(const node_type &rhs)
		{
			*this = rhs;
		}

		Node &operator=(const Node &rhs)
		{
			this->pair  = rhs.pair;
			this->right = rhs.right;
			this->left  = rhs.left;
			this->pair  = rhs.parent;
		}
	};

	template <class Key, class T, class Compare = std::less<Key> >
	class MapBinaryTreeIterator
	{
	public:
		typedef std::pair<Key, T>	pair_type;
		typedef struct Node<Key, T>	node_type;

	private:
		node_type	*node;
		node_type	*root;

	public:

		MapBinaryTreeIterator()
		{
			this->node = NULL;
			this->root = NULL;
		}

		MapBinaryTreeIterator(node_type *node, node_type *root)
		{
			this->node = node;
			this->root = root;
		}

		MapBinaryTreeIterator(const MapBinaryTreeIterator& rhs)
		{
			*this = rhs;
		}

		MapBinaryTreeIterator &operator=(const MapBinaryTreeIterator &rhs)
		{
			this->node = rhs.node;
			this->root = rhs.root;
			return (*this);
		}

		virtual ~MapBinaryTreeIterator()
		{ }

		/*
		 * Element access
		 */

		pair_type &operator*()
		{ return (this->node->pair); }

		pair_type *operator->()
		{ return (&this->node->pair); }

		MapBinaryTreeIterator &operator++()
		{
			if (this->node->right)
			{
				this->node = this->node->right;
				while (this->node->left)
				{ this->node = this->node->left; }
			}
			else
			{
				node_type *temp = this->node;
				this->node = node->parent;
				while (this->node->left != temp)
				{
					temp = this->node;
					this->node = this->node->parent;
				}
			}
			return (*this);
		}

		MapBinaryTreeIterator &operator++(int)
		{
			MapBinaryTreeIterator temp = *this;
			*this++;
			return (temp);
		}

		MapBinaryTreeIterator &operator--()
		{
			if (this->node->left)
			{
				this->node = this->node->left;
				while (this->node->right)
				{ this->node = this->node->right; }
			}
			else
			{
				node_type *temp = this->node;
				this->node = node->parent;
				while (this->node->right != temp)
				{
					temp = this->node;
					this->node = this->node->parent;
				}
			}
			return (*this);
		}

		MapBinaryTreeIterator &operator--(int)
		{
			MapBinaryTreeIterator temp = *this;
			*this--;
			return (temp);
		}

		MapBinaryTreeIterator &operator+=(int x)
		{
			if (x > 0)
			{
				for (int i = 0; i < x; ++i)
				{ *this++; }
			}
			else
			{
				for (int i = 0; i < x; ++i)
				{ *this--; }
			}
			return (*this);
		}

		MapBinaryTreeIterator &operator+(int x) const
		{
			return (operator+=(x));
		}

		MapBinaryTreeIterator &operator-(int x) const
		{
			return (operator+=(-x));
		}

		bool operator ==(const MapBinaryTreeIterator &rhs)
		{ return (this->node == rhs.node); }

		bool operator !=(const MapBinaryTreeIterator &rhs)
		{ return (this->node != rhs.node); }

		bool operator >(const MapBinaryTreeIterator &rhs)
		{ return (this->node > rhs.node); }

		bool operator <(const MapBinaryTreeIterator &rhs)
		{ return (this->node < rhs.node); }

		bool operator <=(const MapBinaryTreeIterator &rhs)
		{ return (this->node <= rhs.node); }

		bool operator >=(const MapBinaryTreeIterator &rhs)
		{ return (this->node >= rhs.node); }
	};

	template <class Key, class T, class Compare = std::less<Key> >
	class BST
	{
		typedef size_t				size_type;
		typedef T					value_type;
		typedef Node<Key, T>		node_type;
		typedef std::pair<Key, T>	pair_type;
		typedef Compare				compare_type;
		typedef value_type*			pointer;
		typedef value_type const*	const_pointer;
		typedef value_type&			reference;
		typedef value_type const	const_reference;

	private:
		node_type		*root;
		node_type		*begin;
		node_type		*end;
		node_type		*len;
		compare_type	compare;

	public:

		BST()
		{
			this->compare = compare_type();
			this->size    = 0;
			this->begin   = new node_type();
			this->end     = begin;
			this->root    = end;
		}

		BST(const BST &rhs)
		{
			this->len     = rhs.len;
			this->begin   = new node_type();
			this->end     = this->begin;
			this->root    = this->end;
			this->copy(rhs);
			this->compare = rhs.compare;
		}

		BST &operator=(const BST &rhs)
		{
			this->clear();
			this->copy(this->rhs);
			this->len = rhs.len;
			this->compare = rhs.compare;
			return (*this);
		}

		virtual ~BST()
		{
			this->clear();
			delete this->end;
		}

		node_type *get_begin() const
		{
			return (this->begin);
		}

		node_type *get_end() const
		{
			return (this->end);
		}

		bool empty() const
		{
			return (this->size() == 0);
		}

		size_type size() const
		{
			return (this->len);
		}

		node_type *insert(node_type *position, pair_type pair)
		{
			node_type *new_node = new node_type(pair);
			if (this->empty())
			{
				this->root = new_node;
				this->len ++;
			}
			else
			{
				this->insert_from_root();
			}
		}
	};
}
#endif