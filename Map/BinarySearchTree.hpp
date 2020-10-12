#ifndef BST_HPP
#define BST_HPP

# include <iostream>
# include <cstddef>
# include <string>
# include <stdio.h>
# include <limits>
# include <memory>
# include <iostream>
# include <string>

namespace ft
{

	// https://www.geeksforgeeks.org/print-level-order-traversal-line-line/?ref=lbp
	// https://www.geeksforgeeks.org/level-order-traversal-line-line-set-2-using-two-queues/?ref=rp
	// https://www.geeksforgeeks.org/level-order-traversal-line-line-set-3-using-one-queue/?ref=rp

	template<
			class Key,
			class T,
			class Compare = std::less<Key> >
	class BST
	{

	public:

		struct Elem
		{
		public:
			std::pair<Key,T>    m_pair;
			struct Elem         *m_left;
			struct Elem         *m_right;
			struct Elem         *m_top;

			// --- Constructors

			// default:
			Elem (void):
					m_pair(), m_left(NULL), m_right(NULL), m_top(NULL) { }

			// overload 1:
			Elem(std::pair<Key,T> p):
					m_pair(p), m_left(NULL), m_right(NULL), m_top(NULL) { }

			// overload 2:
			Elem (std::pair<Key,T> p, Elem *l, Elem *r, Elem *t):
					m_pair(p), m_left(l), m_right(r), m_top(t) { }

			// overload:
			Elem (Elem const &src):
					m_pair(src.m_pair),
					m_left(NULL),
					m_right(NULL),
					m_top(NULL) { }

			Elem &operator=(const Elem& src)
			{
				m_pair = src.m_pair;
				m_left = NULL;
				m_right = NULL;
				m_top = NULL;
			}

			// --- Destructor
			// -

		};

		// ----------------------------------------------------------------

		class BSTIterator
		{

		private:
			// na

		public:
			Elem	*m_elem;
			Elem	*m_root;

			// ----------------------------------------------------------------

			/*
			** --- Coplien form
			*/

			BSTIterator(): m_elem(NULL), m_root(NULL) { }

			BSTIterator(Elem* e, Elem *root):
					m_elem(e),
					m_root(root)
			{ }

			BSTIterator(const BSTIterator& src):
					m_elem(src.m_elem),
					m_root(src.m_root)
			{ }

			BSTIterator &operator=(const BSTIterator& src)
			{
				m_elem = src.m_elem;
				m_root = src.m_root;
				return (*this);
			}

			virtual ~BSTIterator() { }

			// ----------------------------------------------------------------

			/*
			** --- Element access
			*/

			// * Retourne la valeur - Idem qu'en C
			std::pair<Key,T>& operator*() { return (m_elem->m_pair); }
			// Idem qu'en C
			std::pair<Key,T>* operator->() { return (&m_elem->m_pair); }

			// ----------------------------------------------------------------

			/*
			** --- Operators
			*/

			bool operator==(const BSTIterator& src)
			{
				return (m_elem == src.m_elem);
			}

			bool operator!=(const BSTIterator& src)
			{
				return (m_elem != src.m_elem);
			}

			BSTIterator& operator++()
			{
				/*
				**    ->  1
				** 		/   \
				**     ?     3 <- ret (descend jusqu'au prochain droit qui n'a pas de left)
				**         /   \
				**       NULL   5
				*/
				if (m_elem->m_right)
				{
					m_elem = m_elem->m_right;
					while (m_elem->m_left)
						m_elem = m_elem->m_left;
					return (*this);
				}
					/*
					**          3 <- ret
					**         /
					**     -> 2
					** 		/   \
					**     ?    NULL
					*/
					// else if (m_elem
					// 		&& m_elem->m_top
					// 		&& m_elem == m_elem->m_top->m_left)
					// {
					// 	m_elem = m_elem->m_top; // useless, le cas dessous gère ça
					// }
					/*
					**        10 <- ret (on remonte jusqu'au prochain top droite)
					** 		 /
					**      5
					**       \
					**        7 <-
					** 		 / \
					**      ?   NULL
					*/
				else /* if (m_elem->m_top && m_elem->m_top->m_right == m_elem) */
				{
					// Elem *e = m_elem;

					// while (e != m_elem->m_left)
					// {
					// 	e = m_elem;
					// 	m_elem = m_elem->m_top;
					// }

					Elem *e = m_elem;
					m_elem = m_elem->m_top;
					while (m_elem->m_left != e)
					{
						e = m_elem;
						m_elem = m_elem->m_top;
					}
					return (*this);
				}
				/*
				**        7 <- == root
				** 		 / \
				**      ?   NULL
				*/
				// else // ?
				// {
				// m_elem = m_root;
				// while (m_elem && m_elem->m_left)
				// 	m_elem = m_elem->m_left;
				// m_elem = NULL;
				// }
				m_elem = m_root;
				while (m_elem->m_right->m_right)
					m_elem = m_elem->m_right;
				return (*this);
			}

			BSTIterator operator++(int)
			{
				BSTIterator post = *this;
				operator++();
				return (post);
			}

			BSTIterator& operator--()
			{
				if (m_elem && m_elem->m_left)
				{
					m_elem = m_elem->m_left;
					while (m_elem && m_elem->m_right)
						m_elem = m_elem->m_right;
				}
				else if (m_elem)
				{
					Elem *b = m_elem;
					while (m_elem && b != m_elem->m_right)
					{
						b = m_elem;
						m_elem = m_elem->m_top;
					}
				}
				else
				{
					m_elem = m_root;
					while (m_elem && m_elem->m_right)
						m_elem = m_elem->m_right;
				}
				return (*this);
			}

			BSTIterator operator--(int)
			{
				BSTIterator post = *this;
				operator--();
				return (post);
			}

			bool operator==(BSTIterator const &src) const { return (m_elem == src.m_elem); }
			bool operator!=(BSTIterator const &src) const { return (m_elem != src.m_elem); }
			bool operator<(BSTIterator const &src) const { return (m_elem < src.m_elem); }
			bool operator<=(BSTIterator const &src) const { return (m_elem <= src.m_elem); }
			bool operator>(BSTIterator const &src) const { return (m_elem > src.m_elem); }
			bool operator>=(BSTIterator const &src) const { return (m_elem >= src.m_elem); }

			/*
			** --- Possibly useless operators
			*/

			BSTIterator &operator+=(int x) {
				if (x > 0)
				{
					for (int i = 0; i < x; i++)
						operator++();
				}
				else
				{
					for (int i = x; i > 0; i--)
						operator--();
				}
				return (*this);
			}

			BSTIterator operator+(int x) const
			{
				BSTIterator tmp(*this);
				return (tmp += x);
			}

			BSTIterator &operator-=(int x)
			{
				operator+=(-x);
				return (*this);
			}

			BSTIterator operator-(int x) const
			{
				BSTIterator tmp(*this);
				return (tmp -= x);
			}
		};

		// ----------------------------------------------------------------

		class ReverseBSTIterator
		{

		private:
			// na

		public:
			Elem	*m_elem;
			Elem	*m_root;

			// ----------------------------------------------------------------

			/*
			** --- Coplien form
			*/

			ReverseBSTIterator(): m_elem(NULL), m_root(NULL) { }

			ReverseBSTIterator(Elem* e, Elem *root):
					m_elem(e),
					m_root(root)
			{ }

			ReverseBSTIterator(const ReverseBSTIterator& src):
					m_elem(src.m_elem),
					m_root(src.m_root)
			{ }

			ReverseBSTIterator &operator=(const ReverseBSTIterator& src)
			{
				m_elem = src.m_elem;
				m_root = src.m_root;
				return (*this);
			}

			virtual ~ReverseBSTIterator() { }

			// ----------------------------------------------------------------

			/*
			** --- Element access
			*/

			std::pair<Key,T>& operator*() { return (m_elem->m_pair); }

			std::pair<Key,T>* operator->() { return (&m_elem->m_pair); }

			// ----------------------------------------------------------------

			/*
			** --- Operators
			*/

			bool operator==(const ReverseBSTIterator& src)
			{
				return (m_elem == src.m_elem);
			}

			bool operator!=(const ReverseBSTIterator& src)
			{
				return (m_elem != src.m_elem);
			}

			ReverseBSTIterator& operator--()
			{
				/*
				**    ->  1
				** 		/   \
				**     ?     3 <- ret (descend jusqu'au prochain droit qui n'a pas de left)
				**         /   \
				**       NULL   5
				*/
				if (m_elem->m_right)
				{
					m_elem = m_elem->m_right;
					while (m_elem->m_left)
						m_elem = m_elem->m_left;
					return (*this);
				}
					/*
					**          3 <- ret
					**         /
					**     -> 2
					** 		/   \
					**     ?    NULL
					*/
					// else if (m_elem
					// 		&& m_elem->m_top
					// 		&& m_elem == m_elem->m_top->m_left)
					// {
					// 	m_elem = m_elem->m_top; // useless, le cas dessous gère ça
					// }
					/*
					**        10 <- ret (on remonte jusqu'au prochain top droite)
					** 		 /
					**      5
					**       \
					**        7 <-
					** 		 / \
					**      ?   NULL
					*/
				else /* if (m_elem->m_top && m_elem->m_top->m_right == m_elem) */
				{
					// Elem *e = m_elem;

					// while (e != m_elem->m_left)
					// {
					// 	e = m_elem;
					// 	m_elem = m_elem->m_top;
					// }

					Elem *e = m_elem;
					m_elem = m_elem->m_top;
					while (m_elem->m_left != e)
					{
						e = m_elem;
						m_elem = m_elem->m_top;
					}
					return (*this);
				}
				/*
				**        7 <- == root
				** 		 / \
				**      ?   NULL
				*/
				// else // ?
				// {
				// m_elem = m_root;
				// while (m_elem && m_elem->m_left)
				// 	m_elem = m_elem->m_left;
				// m_elem = NULL;
				// }
				m_elem = m_root;
				while (m_elem->m_right->m_right)
					m_elem = m_elem->m_right;
				return (*this);
			}

			ReverseBSTIterator operator--(int)
			{
				ReverseBSTIterator post = *this;
				operator--();
				return (post);
			}

			ReverseBSTIterator& operator++()
			{
				if (m_elem && m_elem->m_left)
				{
					m_elem = m_elem->m_left;
					while (m_elem && m_elem->m_right)
						m_elem = m_elem->m_right;
				}
				else if (m_elem)
				{
					Elem *b = m_elem;
					while (m_elem && b != m_elem->m_right)
					{
						b = m_elem;
						m_elem = m_elem->m_top;
					}
				}
				else // ?
				{
					m_elem = m_root;
					while (m_elem && m_elem->m_right)
						m_elem = m_elem->m_right;
				}
				return (*this);
			}

			ReverseBSTIterator operator++(int)
			{
				ReverseBSTIterator post = *this;
				operator++();
				return (post);
			}

			bool operator==(ReverseBSTIterator const &src) const { return (m_elem == src.m_elem); }
			bool operator!=(ReverseBSTIterator const &src) const { return (m_elem != src.m_elem); }
			bool operator<(ReverseBSTIterator const &src) const { return (m_elem < src.m_elem); }
			bool operator<=(ReverseBSTIterator const &src) const { return (m_elem <= src.m_elem); }
			bool operator>(ReverseBSTIterator const &src) const { return (m_elem > src.m_elem); }
			bool operator>=(ReverseBSTIterator const &src) const { return (m_elem >= src.m_elem); }

			/*
			** --- Possibly useless operators
			*/

			ReverseBSTIterator &operator+=(int x) {
				if (x > 0)
				{
					for (int i = 0; i < x; i++)
						operator++();
				}
				else
				{
					for (int i = x; i > 0; i--)
						operator--();
				}
				return (*this);
			}
			ReverseBSTIterator operator+(int x) const
			{
				ReverseBSTIterator tmp(*this);
				return (tmp += x);
			}

			ReverseBSTIterator &operator-=(int x)
			{
				operator+=(-x);
				return (*this);
			}

			ReverseBSTIterator operator-(int x) const
			{
				ReverseBSTIterator tmp(*this);
				return (tmp -= x);
			}
		};

		// ----------------------------------------------------------------

		/*
		** --- Member types
		*/

	public:

		typedef size_t          size_type;
		typedef T               value_type;
		typedef value_type		*pointer;
		typedef value_type      const *const_pointer;
		typedef value_type		&reference;
		typedef value_type      const &const_reference;

		Elem 		*m_root;
		Compare 	m_comp;

	private:

		Elem 		*m_begin;
		Elem 		*m_end;
		size_t		m_size;

		// ----------------------------------------------------------------

		/*
		** --- Private methods
		*/

	public:

		// ----------------------------------------------------------------

		/*
		** --- Constructors / Destructors
		*/

		BST():
				m_root(NULL), m_comp(), m_size(0)
		{
			m_begin = new Elem();
			m_end = m_begin;
			m_root = m_end;
		}

		BST(BST const &src):
				m_root(NULL), m_comp(src.m_comp), m_size(src.m_size)
		{
			m_begin = new Elem();
			m_end = m_begin;
			m_root = m_end;
			if (!src.empty())
				copyBST(src);
			m_comp = src.m_comp;
		}

		BST &operator=(BST const &src)
		{
			if (!empty())
				clear();
			copyBST(src);
			m_comp = src.m_comp;
			return (*this);
		}

		virtual ~BST()
		{
			if (!empty())
				clear();
			delete m_end;
		}

		// ----------------------------------------------------------------

		/*
		** --- Element access
		*/

		Elem *begin(void) const
		{
			return (m_begin);
		}

		Elem *end(void) const
		{
			return (m_end);
		}

		// ----------------------------------------------------------------

		/*
		** --- Iterators
		*/

		// ----------------------------------------------------------------

		/*
		** --- Capacity
		*/

		bool empty() const { return (m_size == 0); }

		size_t size() const { return (m_size); }

		// ----------------------------------------------------------------

		/*
		** --- Modifiers
		*/

		// insert pair at root
		/* A utility function to insert a new Elem with given p.first in BST */
		Elem *insert(std::pair<Key,T> p)
		{
			return (insertElem(m_root, p));
		}

		// insert pair at hint
		Elem *insertPairAtHint(Elem *hint, std::pair<Key,T> p )
		{
			if (!hint || m_root == m_end
				|| (hint->m_top
					&& (m_comp(p.first, hint->m_top->m_pair.first)
						|| m_comp(hint->m_top->m_pair.first, p.first))))
			{
				return (insert(p));
			}
			else
			{
				Elem *new_e = new Elem(p);
				detach_past_the_elem();
				insertElemAtRoot(hint, new_e);
				splice_past_the_elem();
				return (new_e);
			}
		}

		// insert pair at hint v2
		/* A utility function to insert a new Elem with given p.first in BST */
		Elem *insertElem(struct Elem *e, std::pair<Key,T> p)
		{
			Elem *new_e = new Elem(p);

			/* If the tree is empty, return a new Elem */
			if (m_root == m_end)
			{
				m_root = new_e;
				m_size += 1;
			}
				/* Otherwise, recur down the tree */
			else
			{
				detach_past_the_elem();
				insertElemAtRoot(e, new_e);
			}
			splice_past_the_elem();
			return (new_e);
		}

		// recur down the tree to insert
		void insertElemAtRoot(Elem *root, Elem *new_e)
		{
			if (m_comp(new_e->m_pair.first, root->m_pair.first))
			{
				if (root->m_left)
					return (insertElemAtRoot(root->m_left, new_e));
				root->m_left = new_e;
				m_size += 1;
			}
			else
			{
				if (root->m_right)
					return (insertElemAtRoot(root->m_right, new_e));
				root->m_right = new_e;
				m_size += 1;
			}
			new_e->m_top = root;
		}

		/*
		** --- Display inorder
		*/

		// A utility function to do inorder traversal of BST
		void display(void)
		{
			inorder(m_root);
			std::cout << std::endl;
		}

		// A utility function to do inorder traversal of BST
		void inorder(struct Elem *root)
		{
			if (root != NULL)
			{
				inorder(root->m_left);
				std::cout << root->m_pair.first << ": " << root->m_pair.second << ", ";
				if (root->m_right != m_end)
					inorder(root->m_right);
			}
		}

		/*
		** --- search & find
		*/

		// 0 - point d'entrée
		Elem *find_pair(std::pair<Key,T> p) // appel de base pour rechercher
		{
			Elem *e = find(p.first);
			if (e)
				return (e);
			else
				return (NULL);
		}

		// 1 - point d'entrée
		Elem *find(Key &k)
		{
			Elem *e = find(m_root, k);
			return (e);
		}

		// 2 - root
		Elem *find(struct Elem *root, Key &k)
		{
			Elem *e = findElemWithKey(root, k);
			return (e);
		}

		// 3 - find from root with key
		// pseudo récursivité
		Elem *findElemWithKey(struct Elem *root, Key k)
		{
			if (root == m_end)
				return (NULL);
			while (root != NULL)
			{
				if (k > root->m_pair.first)
					root = root->m_right;
				else if (k < root->m_pair.first)
					root = root->m_left;
				else
					return (root);
			}
			return (root);
		}

		// 1 - point d'entrée | CONST
		Elem *find(const Key &k) const
		{
			Elem *e = find(m_root, k);
			return (e);
		}

		// 2 - root | CONST
		Elem *find(struct Elem *root, const Key &k) const
		{
			Elem *e = findElemWithKey(root, k);
			return (e);
		}

		// 3 - find from root with key | CONST
		Elem *findElemWithKey(struct Elem *root, const Key k) const
		{
			if (root == m_end)
				return (NULL);
			while (root != NULL)
			{
				if (k > root->m_pair.first)
					root = root->m_right;
				else if (k < root->m_pair.first)
					root = root->m_left;
				else
					return (root);
			}
			return (root);
		}

		T& getValueWithKey(Key k)
		{
			return (getValueWithKey(m_root, k));
		}

		T& getValueWithKey(struct Elem *root, Key k)
		{
			while (root != NULL)
			{
				if (k > root->m_pair.first)
					root = root->m_right;
				else if (k < root->m_pair.first)
					root = root->m_left;
				else
					return (root->m_pair.second);
			}
			return (root->m_pair.second);
		}

		// Function to check the given p.first exists or not
		bool contains(std::pair<Key,T> p)
		{
			return (contains(m_root, p));
		}

		// Function to check the given p.first exists or not
		bool contains(struct Elem *root, std::pair<Key,T> p)
		{
			// Traverse untill root reaches to dead end
			while (root != NULL) {
				// pass right subtree as new tree
				if (p.first > root->m_pair.first)
					root = root->m_right;

					// pass left subtree as new tree
				else if (p.first < root->m_pair.first)
					root = root->m_left;
				else
					return (true); // if the p.first is found return (1)
			}
			return (false);
		}

		/*
		** --- Delete
		*/

		/* Given a non-empty binary search tree, return the Elem with minimum
		p.first value found in that tree. Note that the entire tree does not
		need to be searched. */
		Elem *minValueElem(struct Elem *e)
		{
			Elem *current = e;

			/* loop down to find the leftmost leaf */
			while (current && current->m_left != NULL)
				current = current->m_left;

			return current;
		}

		// 1/2
		Elem *deletePair(std::pair<Key,T> p)
		{
			return (deletePair(m_root, p));
		}

		// 2/2
		Elem *deletePair(struct Elem *root, std::pair<Key,T> p)
		{
			// base case
			if (root == NULL) return (root);

			// If the p.first to be deleted is smaller than the root's p.first,
			// then it lies in left subtree
			if (p.first < root->m_pair.first)
				root->m_left = deletePair(root->m_left, p);

				// If the p.first to be deleted is greater than the root's p.first,
				// then it lies in right subtree
			else if (p.first > root->m_pair.first)
				root->m_right = deletePair(root->m_right, p);

				// if p.first is same as root's p.first, then This is the Elem to be deleted
			else
			{
				// Elem with only one child or no child
				if (root->m_left == NULL)
				{
					struct Elem *temp = root->m_right;
					free(root);
					m_size -= 1;
					return (temp);
				}
				else if (root->m_right == NULL)
				{
					struct Elem *temp = root->m_left;
					free(root);
					m_size -= 1;
					return (temp);
				}

				// Elem with two children: Get the inorder successor (smallest
				// in the right subtree)
				Elem *temp = minValueElem(root->m_right);

				// Copy the inorder successor's content to this Elem
				root->m_pair.first = temp->m_pair.first;

				// Delete the inorder successor
				root->m_right = deletePair(root->m_right, temp->m_pair);
			}
			return (root);
		}

		// 1/2 - point d'entrée
		void deleteElem(Elem *e)
		{
			detach_past_the_elem();
			deleteElem(m_root, e);
			splice_past_the_elem();
		}

		// 2/2
		void deleteElem(struct Elem *root, Elem *e)
		{
			deletePair(root, e->m_pair);
		}

		// cf. inorder
		void delete_all(Elem *e)
		{
			if (!e || e == m_end)
				return ;
			delete_all(e->m_left);
			delete_all(e->m_right);
			delete e;
		}

		void clear(void)
		{
			if (empty())
				return ;
			else
			{
				delete_all(m_root);
				m_root = NULL;
				m_end->m_top = NULL;
				m_end->m_left = NULL;
				m_end->m_right = NULL;
				m_begin = m_root = m_end;
				m_size = 0;
			}
		}

		size_type erase(const Key &k)
		{
			Elem *e = NULL;
			size_type count = 0;
			detach_past_the_elem();
			e = find(k);
			if (e)
			{
				deleteElem(e);
				count = 1;
			}
			splice_past_the_elem();
			return (count);
		}

		// ----------------------------------------------------------------

		/*
		** --- ==
		*/

		// function to insert elements of the tree to map m
		// void storeInorder(Elem* root, std::vector<int> &v)
		// {
		// 	if (!root)
		// 		return;
		// 	storeInorder(root->m_left, v);
		// 	v.push_back(root->m_pair.first);
		// 	storeInorder(root->m_right, v);
		// }

		// function to check if the two BSTs contain same set  of elements
		// bool checkBSTsSame(Elem* root1, Elem* root2)
		// {
		// 	// Base cases
		// 	if (!root1 && !root2)
		// 		return true;
		// 	if ((root1 && !root2) || (!root1 && root2))
		// 		return false;

		// 	// Create two std::vectors and store inorder traversals of both BSTs in them.
		// 	std::vector<int> v1, v2;

		// 	storeInorder(root1, v1);
		// 	storeInorder(root2, v2);

		// 	// Return true if both vectors are identical
		// 	return (v1 == v2);
		// }

		// ----------------------------------------------------------------

		/*
		** --- Copy
		*/

		void copyNextElem(Elem **dst, Elem *src, Elem *end)
		{
			if (!src)
				return ;

			*dst = new Elem(*src);

			if (src->m_left)
			{
				copyNextElem(&(*dst)->m_left, src->m_left, end);
				(*dst)->m_left->m_top = *dst;
			}
			if (src->m_right && src->m_right != end)
			{
				copyNextElem(&(*dst)->m_right, src->m_right, end);
				(*dst)->m_right->m_top = *dst;
			}
		}

		void copyBST(const BST &src)
		{

			if (src.m_root == src.m_end)
				return ;

			m_root = new Elem(*src.m_root);

			if (src.m_root->m_left)
			{
				copyNextElem(&m_root->m_left, src.m_root->m_left, src.m_end);
				m_root->m_left->m_top = m_root;
			}

			if (src.m_root->m_right)
			{
				copyNextElem(&m_root->m_right, src.m_root->m_right, src.m_end);
				m_root->m_right->m_top = m_root;
			}
			m_size = src.m_size;
			splice_past_the_elem();
		}

		// ----------------------------------------------------------------

		/*
		** --- Other modifiers
		*/

		void swap(BST &src)
		{
			std::swap(m_root, src.m_root);
			std::swap(m_begin, src.m_begin);
			std::swap(m_end, src.m_end);
			std::swap(m_size, src.m_size);
			std::swap(m_comp, src.m_comp);
		}

	private:

		Elem *copyRoot() const
		{
			return (copyElem(m_root, NULL));
		}

		Elem *copyElem(Elem *e, Elem *top) const
		{
			if (!e)
				return (NULL);
			else
			{
				Elem *e = new Elem(e->m_pair, NULL, NULL, top);
				e->m_left = copyElem(e->m_left, e);
				e->m_right = copyElem(e->m_right, e);
				return (e);
			}
		}

		void splice_past_the_elem(void)
		{
			Elem *e = m_root;
			while (e->m_left)
				e = e->m_left;
			m_begin = e;

			e = m_root;
			while (e->m_right)
				e = e->m_right;
			e->m_right = m_end;
			m_end->m_top = e;
		}

		void detach_past_the_elem(void)
		{
			if (m_end->m_top)
				m_end->m_top->m_right = NULL;
		}
	};

}


#endif