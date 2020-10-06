namespace ft
{
	template <class T>
	struct Less
	{
		typedef T		first_argument_type;
		typedef T		second_argument_type;
		typedef bool	result_type;

		result_type operator() (const first_argument_type& x, const second_argument_type& y)
		{
			return (x < y);
		}
	};
}