#ifndef BST_HPP
# define BST_HPP

# include "iostream"

namespace ft
{
	template<class Key, class T, class Compare = std::less<Key> >

	class BST
	{
	public:
		typedef size_t                                       size_type;
		typedef Compare                                      compare_type;
		typedef Key                                          key_type;
		typedef T                                            mapped_type;
		typedef std::pair<const key_type, mapped_type>       value_type;
		typedef std::pair<const key_type, const mapped_type> const_value_type;

	public:
		struct Node
		{
		public:
			value_type _content;
			Node       *_left;
			Node       *_right;
			Node       *_parent;

			Node()
			{
				this->_left   = NULL;
				this->_right  = NULL;
				this->_parent = NULL;
			}

			Node(value_type pair) : _content(pair)
			{
				this->_left   = NULL;
				this->_right  = NULL;
				this->_parent = NULL;
			}

			Node(const Node &node) : _content(node._content)
			{
				this->_left   = NULL;
				this->_right  = NULL;
				this->_parent = NULL;
			}

			Node &operator=(const Node &rhs)
			{
				this->_parent = rhs._parent;
				this->_left   = rhs._left;
				this->_right  = rhs._right;
				return (*this);
			}

			Node(value_type pair, Node *left, Node *right, Node *parent) : _content(pair)
			{
				this->_left   = left;
				this->_right  = right;
				this->_parent = parent;
			}

			/**
			 * Getters
			 */

			value_type &getContent()
			{
				return this->_content;
			}

		};
		class ConstIterator;
		class Iterator
		{
			typedef Node node_type;
		public:
			node_type *_root;
			node_type *_node;

			Iterator()
			{
				this->_root = NULL;
				this->_node = NULL;
			}

			Iterator(node_type *node, node_type *root)
			{
				this->_root = root;
				this->_node = node;
			}

			Iterator(const Iterator &rhs)
			{
				this->_root = rhs._root;
				this->_node = rhs._node;
			}

			Iterator &operator=(const Iterator &rhs)
			{
				this->_node = rhs._node;
				this->_root = rhs._root;
				return (*this);
			}

			virtual ~Iterator()
			{}

			/*
			 * Access to pair by operators
			 */

			/**
			 * Get the current node value
			 * @return value_type
			 */
			value_type &operator*()
			{
				return (this->_node->getContent());
			}

			/**
			 * Get the current node value address
			 * @return value_type
			 */
			value_type *operator->()
			{
				return (&this->_node->getContent());
			}

			/*
			 * Operators
			 */

			bool operator==(const Iterator &rhs)
			{
				return (this->_node == rhs._node);
			}

			bool operator!=(const Iterator &rhs)
			{
				return (this->_node != rhs._node);
			}

			Iterator &operator++()
			{
				if (this->_node->_right)
				{
					this->_node = this->_node->_right;
					while (this->_node->_left)
					{
						this->_node = this->_node->_left;
					}
					return (*this);
				}
				else
				{
					node_type *n = this->_node;
					this->_node = n->_parent;
					while (this->_node->_left != n)
					{
						n = this->_node;
						this->_node = this->_node->_parent;
					}
					return (*this);
				}
			}

			Iterator operator++(int)
			{
				Iterator tmp = *this;
				operator++();
				return (tmp);
			}

			Iterator &operator--()
			{
				if (this->_node)
				{
					if (this->_node->_left)
					{
						this->_node = this->_node->_left;
						while (this->_node && this->_node->_right)
						{
							this->_node = this->_node->_right;
						}
					}
					else
					{
						node_type *n = this->_node;
						while (this->_node && this->_node->_right != n)
						{
							n = this->_node;
							this->_node = this->_node->_parent;
						}
					}
				}
				else
				{
					this->_node = this->_root;
					while (this->_node && this->_node->_right)
					{
						this->_node = this->_node->_right;
					}
				}
				return (*this);
			}

			Iterator operator--(int)
			{
				Iterator tmp = *this;
				operator--();
				return (tmp);
			}

			node_type *getNode() const
			{
				return (this->_node);
			}

			Iterator(const ConstIterator &x)
			{
				this->_root = x._root;
				this->_root = x._node;
			}

			Iterator &operator=(const ConstIterator &x)
			{
				this->_root = x._root;
				this->_node = x._node;
				return (*this);
			}

			operator ConstIterator()
			{ return (ConstIterator(this->_node, this->_root)); }

			/*
			 * Comparison operators
			 */

			bool operator<(const Iterator &rhs) const
			{
				return _node < rhs._node;
			}

			bool operator>(const Iterator &rhs) const
			{
				return rhs._node < _node;
			}

			bool operator<=(const Iterator &rhs) const
			{
				return !(rhs._node < _node);
			}

			bool operator>=(const Iterator &rhs) const
			{
				return !(_node < rhs._node);
			}
		};
		class ConstIterator
		{
			typedef Node node_type;

		public:
			node_type *_root;
			node_type *_node;

			ConstIterator()
			{
				this->_root = NULL;
				this->_node = NULL;
			}

			ConstIterator(node_type *node, node_type *root)
			{
				this->_root = root;
				this->_node = node;
			}

			ConstIterator(const ConstIterator &rhs)
			{
				this->_root = rhs._root;
				this->_node = rhs._node;
			}

			ConstIterator &operator=(const ConstIterator &rhs)
			{
				this->_node = rhs._node;
				this->_root = rhs._root;
				return (*this);
			}

			virtual ~ConstIterator()
			{}

			ConstIterator(const Iterator &x)
			{
				this->_root = x._root;
				this->_root = x._node;
			}

			ConstIterator &operator=(const Iterator &x)
			{
				this->_root = x._root;
				this->_node = x._node;
				return (*this);
			}

			operator Iterator()
			{ return (Iterator(this->_node, this->_root)); }

			/*
			 * Access to pair by operators
			 */

			/**
			 * Get the current node value
			 * @return value_type
			 */
			const value_type &operator*()
			{
				return (this->_node->getContent());
			}

			/**
			 * Get the current node value address
			 * @return value_type
			 */
			const value_type *operator->()
			{
				return (&this->_node->getContent());
			}

			/*
			 * Operators
			 */

			bool operator==(const ConstIterator &rhs)
			{
				return (this->_node == rhs._node);
			}

			bool operator!=(const ConstIterator &rhs)
			{
				return (this->_node != rhs._node);
			}

			ConstIterator &operator++()
			{
				if (this->_node->_right)
				{
					this->_node = this->_node->_right;
					while (this->_node->_left)
					{
						this->_node = this->_node->_left;
					}
					return (*this);
				}
				else
				{
					node_type *n = this->_node;
					this->_node = n->_parent;
					while (this->_node->_left != n)
					{
						n = this->_node;
						this->_node = this->_node->_parent;
					}
					return (*this);
				}
			}

			ConstIterator operator++(int)
			{
				ConstIterator tmp = *this;
				operator++();
				return (tmp);
			}

			ConstIterator &operator--()
			{
				if (this->_node)
				{
					if (this->_node->_left)
					{
						this->_node = this->_node->_left;
						while (this->_node && this->_node->_right)
						{
							this->_node = this->_node->_right;
						}
					}
					else
					{
						node_type *n = this->_node;
						while (this->_node && this->_node->_right != n)
						{
							n = this->_node;
							this->_node = this->_node->_parent;
						}
					}
				}
				else
				{
					this->_node = this->_root;
					while (this->_node && this->_node->_right)
					{
						this->_node = this->_node->_right;
					}
				}
				return (*this);
			}

			ConstIterator operator--(int)
			{
				ConstIterator tmp = *this;
				operator--();
				return (tmp);
			}

			node_type *getNode() const
			{
				return (this->_node);
			}

			/*
			 * Comparison operators
			 */

			bool operator<(const ConstIterator &rhs) const
			{
				return _node < rhs._node;
			}

			bool operator>(const ConstIterator &rhs) const
			{
				return rhs._node < _node;
			}

			bool operator<=(const ConstIterator &rhs) const
			{
				return !(rhs._node < _node);
			}

			bool operator>=(const ConstIterator &rhs) const
			{
				return !(_node < rhs._node);
			}
		};
		class ConstReverseIterator;
		class ReverseIterator
		{
			typedef Node node_type;
		public:
			node_type *_root;
			node_type *_node;

			ReverseIterator()
			{
				this->_root = NULL;
				this->_node = NULL;
			}

			ReverseIterator(node_type *node, node_type *root)
			{
				this->_root = root;
				this->_node = node;
			}

			ReverseIterator(const ReverseIterator &rhs)
			{
				this->_root = rhs._root;
				this->_node = rhs._node;
			}

			ReverseIterator &operator=(const ReverseIterator &rhs)
			{
				this->_node = rhs._node;
				this->_root = rhs._root;
				return (*this);
			}

			virtual ~ReverseIterator()
			{}

			ReverseIterator(const ConstReverseIterator &x)
			{
				this->_root = x._root;
				this->_root = x._node;
			}

			ReverseIterator &operator=(const ConstReverseIterator &x)
			{
				this->_root = x._root;
				this->_node = x._node;
				return (*this);
			}

			operator ConstReverseIterator()
			{ return (ConstReverseIterator(this->_node, this->_root)); }

			/*
			 * Access to pair by operators
			 */

			/**
			 * Get the current node value
			 * @return value_type
			 */
			value_type &operator*()
			{
				return (this->_node->getContent());
			}

			/**
			 * Get the current node value address
			 * @return value_type
			 */
			value_type *operator->()
			{
				return (&this->_node->getContent());
			}

			/*
			 * Operators
			 */

			bool operator==(const ReverseIterator &rhs)
			{
				return (this->_node == rhs._node);
			}

			bool operator!=(const ReverseIterator &rhs)
			{
				return (this->_node != rhs._node);
			}

			ReverseIterator &operator--()
			{
				if (this->_node->_right)
				{
					this->_node = this->_node->_right;
					while (this->_node->_left)
					{
						this->_node = this->_node->_left;
					}
					return (*this);
				}
				else
				{
					node_type *n = this->_node;
					this->_node = n->_parent;
					while (this->_node->_left != n)
					{
						n = this->_node;
						this->_node = this->_node->_parent;
					}
					return (*this);
				}
			}

			ReverseIterator operator--(int)
			{
				Iterator tmp = *this;
				operator--();
				return (tmp);
			}

			ReverseIterator &operator++()
			{
				if (this->_node)
				{
					if (this->_node->_left)
					{
						this->_node = this->_node->_left;
						while (this->_node && this->_node->_right)
						{
							this->_node = this->_node->_right;
						}
					}
					else
					{
						node_type *n = this->_node;
						while (this->_node && this->_node->_right != n)
						{
							n = this->_node;
							this->_node = this->_node->_parent;
						}
					}
				}
				else
				{
					this->_node = this->_root;
					while (this->_node && this->_node->_right)
					{
						this->_node = this->_node->_right;
					}
				}
				return (*this);
			}

			ReverseIterator operator++(int)
			{
				ReverseIterator tmp = *this;
				operator++();
				return (tmp);
			}

			node_type *getNode() const
			{
				return (this->_node);
			}

			/*
			 * Comparison operators
			 */

			bool operator<(const ReverseIterator &rhs) const
			{
				return _node < rhs._node;
			}

			bool operator>(const ReverseIterator &rhs) const
			{
				return rhs._node < _node;
			}

			bool operator<=(const ReverseIterator &rhs) const
			{
				return !(rhs._node < _node);
			}

			bool operator>=(const ReverseIterator &rhs) const
			{
				return !(_node < rhs._node);
			}
		};
		class ConstReverseIterator
		{
			typedef Node node_type;
		public:
			node_type *_root;
			node_type *_node;

			ConstReverseIterator()
			{
				this->_root = NULL;
				this->_node = NULL;
			}

			ConstReverseIterator(node_type *node, node_type *root)
			{
				this->_root = root;
				this->_node = node;
			}

			ConstReverseIterator(const ConstReverseIterator &rhs)
			{
				this->_root = rhs._root;
				this->_node = rhs._node;
			}

			ConstReverseIterator &operator=(const ConstReverseIterator &rhs)
			{
				this->_node = rhs._node;
				this->_root = rhs._root;
				return (*this);
			}

			virtual ~ConstReverseIterator()
			{}

			ConstReverseIterator(const ReverseIterator &x)
			{
				this->_root = x._root;
				this->_root = x._node;
			}

			ConstReverseIterator &operator=(const ReverseIterator &x)
			{
				this->_root = x._root;
				this->_node = x._node;
				return (*this);
			}

			operator ReverseIterator()
			{ return (ReverseIterator(this->_node, this->_root)); }

			/*
			 * Access to pair by operators
			 */

			/**
			 * Get the current node value
			 * @return value_type
			 */
			const value_type &operator*()
			{
				return (this->_node->getContent());
			}

			/**
			 * Get the current node value address
			 * @return value_type
			 */
			const value_type *operator->()
			{
				return (&this->_node->getContent());
			}

			/*
			 * Operators
			 */

			bool operator==(const ConstReverseIterator &rhs)
			{
				return (this->_node == rhs._node);
			}

			bool operator!=(const ConstReverseIterator &rhs)
			{
				return (this->_node != rhs._node);
			}

			ConstReverseIterator &operator--()
			{
				if (this->_node->_right)
				{
					this->_node = this->_node->_right;
					while (this->_node->_left)
					{
						this->_node = this->_node->_left;
					}
					return (*this);
				}
				else
				{
					node_type *n = this->_node;
					this->_node = n->_parent;
					while (this->_node->_left != n)
					{
						n = this->_node;
						this->_node = this->_node->_parent;
					}
					return (*this);
				}
			}

			ConstReverseIterator operator--(int)
			{
				Iterator tmp = *this;
				operator--();
				return (tmp);
			}

			ConstReverseIterator &operator++()
			{
				if (this->_node)
				{
					if (this->_node->_left)
					{
						this->_node = this->_node->_left;
						while (this->_node && this->_node->_right)
						{
							this->_node = this->_node->_right;
						}
					}
					else
					{
						node_type *n = this->_node;
						while (this->_node && this->_node->_right != n)
						{
							n = this->_node;
							this->_node = this->_node->_parent;
						}
					}
				}
				else
				{
					this->_node = this->_root;
					while (this->_node && this->_node->_right)
					{
						this->_node = this->_node->_right;
					}
				}
				return (*this);
			}

			ConstReverseIterator operator++(int)
			{
				ConstReverseIterator tmp = *this;
				operator++();
				return (tmp);
			}

			node_type *getNode() const
			{
				return (this->_node);
			}

			/*
			 * Comparison operators
			 */

			bool operator<(const ConstReverseIterator &rhs) const
			{
				return _node < rhs._node;
			}

			bool operator>(const ConstReverseIterator &rhs) const
			{
				return rhs._node < _node;
			}

			bool operator<=(const ConstReverseIterator &rhs) const
			{
				return !(rhs._node < _node);
			}

			bool operator>=(const ConstReverseIterator &rhs) const
			{
				return !(_node < rhs._node);
			}
		};
		typedef Node node_type;

	private:
		node_type    *_begin;
		node_type    *_end;
		node_type    *_root;
		size_type    _len;
		compare_type _compare;

		void init_variables(node_type *begin = NULL, node_type *end = new node_type(), node_type *root = NULL,
							size_type len = 0, compare_type compare = compare_type())
		{
			this->_begin   = begin;
			this->_end     = end;
			this->_root    = root;
			this->_len     = len;
			this->_compare = compare;
		}

		void increase_size(const int n = 1)
		{
			this->_len += n;
		}

		void set_tree_bounds()
		{
			node_type *node = this->_root;
			while (node->_left)
			{
				node = node->_left;
			}
			this->_begin        = node;
			this->_begin->_left = NULL;

			node = this->_root;
			while (node->_right)
			{
				node = node->_right;
			}
			node->_right        = this->_end;
			this->_end->_parent = node;
			this->_end->_right  = NULL;
		}

		void remove_last_node()
		{
			if (this->end()->_parent)
				this->_end->_parent->_right = NULL;
		}

	public:

		/*
		 * Constructors and destructors
		 */

		BST()
		{
			this->init_variables();
		}

		BST(const BST &rhs)
		{
			this->init_variables(NULL, NULL, NULL, rhs._len, rhs._compare);
			this->_begin = new node_type();
			this->_end   = this->_begin;
			this->_root  = this->_end;
			this->copyFrom(rhs);
		}

		BST &operator=(const BST &rhs)
		{
			this->clear_tree();
			this->copyFrom(rhs);
			this->_compare = rhs._compare;
			return (*this);
		}

		virtual ~BST()
		{
			this->clear_tree();
			delete this->_end;
		}

		/*
		 * Access functions and capacity function
		 */

		node_type *begin()
		{
			return (this->_begin);
		}

		node_type *end()
		{
			return (this->_end);
		}

		node_type *end() const
		{
			return (this->_end);
		}

		node_type *root()
		{
			return (this->_root);
		}

		node_type *root() const
		{
			return (this->_root);
		}

		size_type size() const
		{
			return (this->_len);
		}

		bool empty()
		{
			return (this->size() == 0);
		}

		/*
		 * Modifiers
		 */

		node_type *insert(value_type pair)
		{
			node_type *inserted = insert_at_position(this->_root, pair);
			return (inserted);
		}

		node_type *insert_at_position(node_type *position_node, value_type pair)
		{
			node_type *new_node = new node_type(pair);
			if (this->size() == 0)
			{
				this->_root = new_node;
				this->increase_size();
			}
			else
			{
				// in this case, we need to insert the element as the right place using comparison
				this->remove_last_node();
				this->recursive_insert(position_node, new_node);
			}
			this->set_tree_bounds();
			return (new_node);
		}

		void recursive_insert(node_type *from_node, node_type *node_to_insert)
		{
			if (this->_compare(node_to_insert->_content.first, from_node->_content.first))
			{
				if (from_node->_left)
				{
					// we are not at the right place to insert
					this->recursive_insert(from_node->_left, node_to_insert);
					return;
				}
				// insert the element
				from_node->_left = node_to_insert;
			}
			else
			{
				if (from_node->_right)
				{
					// we are not at the right place to insert
					this->recursive_insert(from_node->_right, node_to_insert);
					return;
				}
				// insert the element
				from_node->_right = node_to_insert;
			}
			this->increase_size();
			node_to_insert->_parent = from_node;
		}

		static void print2DUtil(node_type *root, int space)
		{
			int COUNT = 7;
			// Base case
			if (root == NULL)
				return;

			// Increase distance between levels
			space += COUNT;

			// Process right child first
//			std::cout << root->_right->getContent().first << std::endl;
//			return ;
			print2DUtil(root->_right, space);

			// Print current node after space
			// count
			std::cout << '\n';
			for (int i = COUNT; i < space; i++)
				std::cout << " ";
			std::cout << root->_content.first << "->" << root->_content.second << std::endl;

			// Process left child
			print2DUtil(root->_left, space);
		}

		static void print2D(node_type *root)
		{
			// Pass initial space count as 0
			print2DUtil(root, 0);
		}

		void print()
		{
			print2D(this->_root);
		}

		node_type *recurse_find_elem(node_type *from_node, key_type key) {
			if (from_node == NULL)
			{
				return (NULL);
			}
			while (from_node != NULL)
			{
				if (key > from_node->_content.first)
				{
					from_node = from_node->_right;
				}
				else if (from_node->_content.first > key)
				{
					from_node = from_node->_left;
				}
				else
				{
					return (from_node);
				}
			}
			return (NULL);
		}

		node_type *find_by_key_with_root(node_type *root, key_type key) {
			return (recurse_find_elem(root, key));
		}

		node_type *find_by_key(key_type key)
		{
			node_type *node = find_by_key_with_root(this->root(), key);
			return (node);
		}


		node_type *recurse_find_elem(node_type *from_node, const key_type key) const {
			if (from_node == NULL)
			{
				return (NULL);
			}
			while (from_node != NULL)
			{
				if (key > from_node->_content.first)
				{
					from_node = from_node->_right;
				}
				else if (from_node->_content.first > key)
				{
					from_node = from_node->_left;
				}
				else
				{
					return (from_node);
				}
			}
			return (NULL);
		}

		node_type *find_by_key_with_root(node_type *root, const key_type key) const {
			return (recurse_find_elem(root, key));
		}

		node_type *find_by_key(const key_type key) const
		{
			node_type *node = find_by_key_with_root(this->root(), key);
			return (node);
		}

		node_type *find_by_pair(node_type *from_node, value_type pair)
		{
			if (from_node == NULL)
			{
				from_node = this->root();
			}
			if (from_node == NULL)
			{
				return (NULL);
			}
			while (from_node != NULL)
			{
				if (pair > from_node->_content)
				{
					from_node = from_node->_right;
				}
				else if (pair < from_node->_content)
				{
					from_node = from_node->_left;
				}
				else
				{
					return (from_node);
				}
			}
			return (NULL);
		}

		T &get_value_from_key(Key k)
		{
			node_type *node = this->find_by_key(_root, k);
			if (node)
			{
				return (node->_content.second);
			}
			else
			{
				throw std::logic_error("this key does not exists");
			}
		}

		bool contains(value_type pair)
		{
			return (this->find_by_pair(pair) != NULL);
		}

		bool contains(key_type key)
		{
			return (this->contains_key(key) != NULL);
		}

		node_type *get_left_value(node_type *from_root)
		{
			node_type *tmp = from_root;
			while (tmp && tmp->_left != NULL)
			{
				tmp = tmp->_left;
			}
			return (tmp);
		}

		size_type erase_from_key(const key_type &key)
		{
			node_type *found = find_by_key(key);
			if (found != NULL)
			{
				delete_node(this->root(), found->getContent().first);
				this->increase_size(-1);
				set_tree_bounds();
			}
			return (found != NULL ? 1 : 0);
		}

		void search_key(node_type *&curr, key_type key, node_type *&parent)
		{
			while (curr != NULL && curr->getContent().first != key)
			{
				parent = curr;
				if (key < curr->getContent().first)
				{
					curr = curr->_left;
				}
				else
				{
					curr = curr->_right;
				}
			}
		}

		node_type *minimum_key(node_type *curr)
		{
			while (curr->_left != NULL)
			{
				curr = curr->_left;
			}
			return (curr);
		}

		void delete_node(node_type *root, key_type key)
		{
			node_type *parent = NULL;
			node_type *curr   = root;
			search_key(curr, key, parent);

			if (curr == NULL)
			{
				return;
			}

			if (curr->_left == NULL && curr->_right == NULL)
			{
				if (curr != this->root())
				{
					if (parent->_left == curr)
					{
						parent->_left = NULL;
					}
					else
					{
						parent->_right = NULL;
					}
				}
				else
				{
					this->_root = NULL;
				}
				delete curr;
			}
			else if (curr->_left && curr->_right)
			{
				node_type  *successor = minimum_key(curr->_right);
				value_type val        = successor->getContent();
				delete_node(root, val.first);
//				curr->setContent(val);
//				curr->_content = val;
				curr->_content.second = val.second;
			}
			else
			{
				node_type *child = (curr->_left) ? curr->_left : curr->_right;
				if (curr != root)
				{
					if (curr == parent->_left)
					{
						parent->_left = child;
					}
					else
					{
						parent->_right = child;
					}
				}
				else
				{
					_root = child;
				}
				delete (curr);
			}
		}

		void recursive_free(node_type *node)
		{
			if (node == NULL || node == this->end())
			{
				return;
			}
			this->recusrive_free(node->_left);
			this->recusrive_free(node->_right);
			delete node;
		}

		void clear_tree()
		{
			if (this->empty())
			{ return; }
			this->_root         = NULL;
			this->_end->_parent = NULL;
			this->_end->_left   = NULL;
			this->_end->_right  = NULL;
			this->_root         = this->end();
			this->_begin        = this->root();
			this->_len          = 0;
		}

		void copyNextNode(node_type **dest, node_type *from, node_type *end)
		{
			if (from == NULL)
			{
				return;
			}
			*dest = new node_type(*from);
			if (from->_left)
			{
				this->copyNextNode(&(*dest)->_left, from->_left, end);
				(*dest)->_left->_parent = *dest;
			}
			if (from->_right && from->_right != end)
			{
				this->copyNextNode(&(*dest)->_right, from->_right, end);
				(*dest)->_right->_parent = *dest;
			}
		}

		void copyFrom(const BST &x)
		{
			if (x._len == 0 || x._root == x._end)
			{
				return;
			}
			this->_root = new Node(*x._root);
			if (x._root->_left)
			{
				this->copyNextNode(&this->_root->_left, x._root->_left, x._end);
				this->_root->_left->_parent = this->_root;
			}
			if (x._root->_right && x._root->_right != x._end)
			{
				this->copyNextNode(&_root->_right, x._root->_right, x._end);
				this->_root->_right->_parent = this->_root;
			}
			this->_len  = x._len;
			this->set_tree_bounds();
		}

		/*
		 * Getters
		 */

		node_type *getBegin() const
		{
			return _begin;
		}

		node_type *getEnd() const
		{
			return _end;
		}

		node_type *getRoot() const
		{
			return _root;
		}

		size_type getLen() const
		{
			return _len;
		}

		compare_type getCompare() const
		{
			return _compare;
		}
	};
}

#endif