#ifndef VECTORS_ITERATORS_HPP
# define VECTORS_ITERATORS_HPP

# include <iostream>

namespace ft
{

	template<typename T>
	class ConstVectorIterator;

	template<typename T>
	class VectorIterator
	{
	public:
		typedef T              value_type;
		typedef T              &reference;
		typedef T              *pointer;
		typedef std::ptrdiff_t difference_type;

	private:
		pointer ptr_content;

	public:

		VectorIterator(void)
		{ ptr_content = NULL; }

		VectorIterator(pointer ptr_content)
		{ this->ptr_content = ptr_content; }

		VectorIterator(const VectorIterator &x)
		{ this->ptr_content = x.ptr_content; }

		~VectorIterator()
		{}

		VectorIterator<value_type> &operator=(const VectorIterator<value_type> &rhs)
		{
			this->ptr_content = rhs.ptr_content;
			return (*this);
		}

		VectorIterator(const ConstVectorIterator<T> &x)
		{
			this->ptr_content = x.ptr_content;
		}

		VectorIterator &operator=(const ConstVectorIterator <T> &x)
		{
			this->ptr_content = x.ptr_content;
			return (*this);
		}

		operator ConstVectorIterator<T>()
		{
			return (ConstVectorIterator<T>(this->ptr_content));
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

		bool operator==(const VectorIterator &rhs)
		{
			return (this->ptr_content == rhs.ptr_content);
		}

		bool operator!=(const VectorIterator &rhs)
		{
			return (this->ptr_content != rhs.ptr_content);
		}

		bool operator<(const VectorIterator &rhs)
		{
			return (this->ptr_content < rhs.ptr_content);
		}

		bool operator>(const VectorIterator &rhs)
		{
			return (this->ptr_content > rhs.ptr_content);
		}

		bool operator<=(const VectorIterator &rhs)
		{
			return (this->ptr_content <= rhs.ptr_content);
		}

		bool operator>=(const VectorIterator &rhs)
		{
			return (this->ptr_content >= rhs.ptr_content);
		}
	};
	template<typename T>
	class ConstVectorIterator
	{
	public:
		typedef T              value_type;
		typedef const T        &reference;
		typedef const T        *pointer;
		typedef std::ptrdiff_t difference_type;

	private:
		pointer ptr_content;

	public:

		ConstVectorIterator(void)
		{ ptr_content = NULL; }

		ConstVectorIterator(pointer ptr_content)
		{ this->ptr_content = ptr_content; }

		ConstVectorIterator(const ConstVectorIterator &x)
		{ this->ptr_content = x.ptr_content; }

		~ConstVectorIterator()
		{}

		ConstVectorIterator<value_type> &operator=(const ConstVectorIterator<value_type> &rhs)
		{
			this->ptr_content = rhs.ptr_content;
			return (*this);
		}

		ConstVectorIterator(const ListIterator <T> &x)
		{
			this->ptr_content = x.ptr_content;
		}

		ConstVectorIterator &operator=(const ListIterator <T> &x)
		{
			this->ptr_content = x.ptr_content;
			return (*this);
		}

		operator ListIterator<T>()
		{
			return (ListIterator<T>(this->ptr_content));
		}

		/*
		 * Arithmetic Operators
		 */

		ConstVectorIterator<T> &operator++()
		{
			this->ptr_content++;
			return (*this);
		}

		ConstVectorIterator<T> operator++(int)
		{
			ConstVectorIterator<T> it = *this;
			this->ptr_content++;
			return (it);
		}

		ConstVectorIterator<T> &operator--()
		{
			this->ptr_content--;
			return (*this);
		}

		ConstVectorIterator<T> operator--(int)
		{
			ConstVectorIterator<T> it = *this;
			this->ptr_content--;
			return (it);
		}

		ConstVectorIterator<T> operator+(difference_type n)
		{
			return (ConstVectorIterator<value_type>(this->ptr_content + n));
		}

		ConstVectorIterator<T> operator+(ConstVectorIterator<value_type> x)
		{

			return (this->ptr_content + x.ptr_content);
		}

		ConstVectorIterator<T> operator-(difference_type n)
		{
			return (ConstVectorIterator<value_type>(this->ptr_content - n));
		}

		difference_type operator-(ConstVectorIterator<value_type> x)
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

		ConstVectorIterator<T> &operator+=(difference_type n)
		{
			this->ptr_content += n;
			return (*this);
		}

		ConstVectorIterator<T> &operator-=(difference_type n)
		{
			this->ptr_content -= n;
			return (*this);
		}

		/*
		 * Equality operators
		 */

		bool operator==(const ConstVectorIterator &rhs)
		{
			return (this->ptr_content == rhs.ptr_content);
		}

		bool operator!=(const ConstVectorIterator &rhs)
		{
			return (this->ptr_content != rhs.ptr_content);
		}

		bool operator<(const ConstVectorIterator &rhs)
		{
			return (this->ptr_content < rhs.ptr_content);
		}

		bool operator>(const ConstVectorIterator &rhs)
		{
			return (this->ptr_content > rhs.ptr_content);
		}

		bool operator<=(const ConstVectorIterator &rhs)
		{
			return (this->ptr_content <= rhs.ptr_content);
		}

		bool operator>=(const ConstVectorIterator &rhs)
		{
			return (this->ptr_content >= rhs.ptr_content);
		}
	};
	template<typename T>
	class ConstReverseVectorIterator;
	template<class T>
	class ReverseVectorIterator
	{
	public:
		typedef T              value_type;
		typedef T              &reference;
		typedef T              *pointer;
		typedef std::ptrdiff_t difference_type;

	private:
		pointer ptr_content;

	public:

		ReverseVectorIterator(void)
		{ ptr_content = NULL; }

		ReverseVectorIterator(pointer ptr_content)
		{ this->ptr_content = ptr_content; }

		ReverseVectorIterator(const ReverseVectorIterator &x)
		{ this->ptr_content = x.ptr_content; }

		~ReverseVectorIterator()
		{}

		ReverseVectorIterator<value_type> &operator=(const ReverseVectorIterator<value_type> &rhs)
		{
			this->ptr_content = rhs.ptr_content;
			return (*this);
		}

		ReverseVectorIterator(const ConstReverseVectorIterator<T> &x)
		{
			this->ptr_content = x.ptr_content;
		}

		ReverseVectorIterator &operator=(const ConstReverseVectorIterator<T> &x)
		{
			this->ptr_content = x.ptr_content;
			return (*this);
		}

		operator ConstReverseVectorIterator<T>()
		{
			return (ConstReverseVectorIterator<T>(this->ptr_content));
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

		bool operator==(const ReverseVectorIterator &rhs)
		{
			return (this->ptr_content == rhs.ptr_content);
		}

		bool operator!=(const ReverseVectorIterator &rhs)
		{
			return (this->ptr_content != rhs.ptr_content);
		}

		bool operator<(const ReverseVectorIterator &rhs)
		{
			return (this->ptr_content < rhs.ptr_content);
		}

		bool operator>(const ReverseVectorIterator &rhs)
		{
			return (this->ptr_content > rhs.ptr_content);
		}

		bool operator<=(const ReverseVectorIterator &rhs)
		{
			return (this->ptr_content <= rhs.ptr_content);
		}

		bool operator>=(const ReverseVectorIterator &rhs)
		{
			return (this->ptr_content >= rhs.ptr_content);
		}
	};
	template<class T>
	class ConstReverseVectorIterator
	{
	public:
		typedef T              value_type;
		typedef const T        &reference;
		typedef const T        *pointer;
		typedef std::ptrdiff_t difference_type;

	private:
		pointer ptr_content;

	public:

		ConstReverseVectorIterator(void)
		{ ptr_content = NULL; }

		ConstReverseVectorIterator(pointer ptr_content)
		{ this->ptr_content = ptr_content; }

		ConstReverseVectorIterator(const ConstReverseVectorIterator &x)
		{ this->ptr_content = x.ptr_content; }

		~ConstReverseVectorIterator()
		{}

		ConstReverseVectorIterator<value_type> &operator=(const ConstReverseVectorIterator<value_type> &rhs)
		{
			this->ptr_content = rhs.ptr_content;
			return (*this);
		}

		ConstReverseVectorIterator(const ReverseVectorIterator<T> &x)
		{
			this->ptr_content = x.ptr_content;
		}

		ConstReverseVectorIterator &operator=(const ReverseVectorIterator<T> &x)
		{
			this->ptr_content = x.ptr_content;
			return (*this);
		}

		operator ReverseVectorIterator<T>()
		{
			return (ReverseVectorIterator<T>(this->ptr_content));
		}

		/*
		 * Arithmetic Operators
		 */

		ConstReverseVectorIterator<T> &operator++()
		{
			this->ptr_content--;
			return (*this);
		}

		ConstReverseVectorIterator<T> operator++(int)
		{
			ConstReverseVectorIterator<T> it = *this;
			this->ptr_content--;
			return (it);
		}

		ConstReverseVectorIterator<T> &operator--()
		{
			this->ptr_content++;
			return (*this);
		}

		ConstReverseVectorIterator<T> operator--(int)
		{
			ConstReverseVectorIterator<T> it = *this;
			this->ptr_content++;
			return (it);
		}

		ConstReverseVectorIterator<T> operator+(difference_type n)
		{
			return (ConstReverseVectorIterator<value_type>(this->ptr_content - n));
		}

		ConstReverseVectorIterator<T> operator+(ConstReverseVectorIterator<value_type> x)
		{
			return (ConstReverseVectorIterator<value_type>(this->ptr_content - x.ptr_content));
		}

		ConstReverseVectorIterator<T> operator-(difference_type n)
		{
			return (ConstReverseVectorIterator<value_type>(this->ptr_content - n));
		}

		difference_type operator-(ConstReverseVectorIterator<value_type> x)
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

		ConstReverseVectorIterator<T> &operator+=(difference_type n)
		{
			this->ptr_content -= n;
			return (*this);
		}

		ConstReverseVectorIterator<T> &operator-=(difference_type n)
		{
			this->ptr_content += n;
			return (*this);
		}

		/*
		 * Equality operators
		 */

		bool operator==(const ConstReverseVectorIterator &rhs)
		{
			return (this->ptr_content == rhs.ptr_content);
		}

		bool operator!=(const ConstReverseVectorIterator &rhs)
		{
			return (this->ptr_content != rhs.ptr_content);
		}

		bool operator<(const ConstReverseVectorIterator &rhs)
		{
			return (this->ptr_content < rhs.ptr_content);
		}

		bool operator>(const ConstReverseVectorIterator &rhs)
		{
			return (this->ptr_content > rhs.ptr_content);
		}

		bool operator<=(const ConstReverseVectorIterator &rhs)
		{
			return (this->ptr_content <= rhs.ptr_content);
		}

		bool operator>=(const ConstReverseVectorIterator &rhs)
		{
			return (this->ptr_content >= rhs.ptr_content);
		}
	};
}

#endif