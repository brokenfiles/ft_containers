#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft
{
	template<class T1, class T2>
	struct pair
	{
		typedef T1  first_type;
		typedef T2  second_type;
		first_type  first;
		second_type second;

		pair()
		{
			this->first  = first_type();
			this->second = second_type();
		}

		template<class U, class V>
		pair(const pair<U, V> &pr)
		{
			this->first = pr.first;
			this->second = pr.second;
		}


	};
}
#endif