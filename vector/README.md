**Member Types**


	member type				definition																				notes

	value_type				The first template parameter (T)	
	allocator_type			The second template parameter (Alloc)													defaults to: allocator<value_type>
	reference				allocator_type::reference																for the default allocator: value_type&
	const_reference			allocator_type::const_reference															for the default allocator: const value_type&
	pointer					allocator_type::pointer																	for the default allocator: value_type*
	const_pointer			allocator_type::const_pointer															for the default allocator: const value_type*
	iterator				a random access iterator to value_type													convertible to const_iterator
	const_iterator			a random access iterator to const value_type	
	reverse_iterator		reverse_iterator<iterator>	
	const_reverse_iterator	reverse_iterator<const_iterator>	
	difference_type			a signed integral type, identical to: iterator_traits<iterator>::difference_type		usually the same as ptrdiff_t
	size_type				an unsigned integral type that can represent any non-negative value of difference_type	usually the same as size_t


