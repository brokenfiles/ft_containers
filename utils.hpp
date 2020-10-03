namespace ft
{
	template<typename T>
	void swap(T& one, T& second)
	{
		T tmp = second;
		second = one;
		one = tmp;
	}
}