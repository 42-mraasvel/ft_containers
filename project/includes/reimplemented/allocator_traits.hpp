#ifndef ALLOCATOR_TRAITS_HPP
# define ALLOCATOR_TRAITS_HPP

namespace ft {

template <class Alloc>
struct allocator_traits {
public:

	typedef Alloc															allocator_type;

	typedef typename allocator_type::value_type								value_type;
	typedef typename allocator_type::pointer								pointer;
	typedef typename allocator_type::const_ponter							const_pointer;
	typedef typename allocator_type::reference								reference;
	typedef typename allocator_type::const_reference						const_reference;
	typedef typename allocator_type::size_type								size_type;
	typedef typename allocator_type::difference_type						difference_type;
	typedef typename allocator_type::template rebind<value_type>::other		rebind_alloc;

	typedef typename allocator_type::void_pointer							void_pointer;
	typedef typename allocator_type::const_void_pointer						const_void_pointer;


	static pointer allocate(allocator_type& alloc, size_type n) {
		return alloc.allocate(n);
	}

	static pointer allocate(allocator_type& alloc, size_type n, const_void_pointer hint) {
		return alloc.allocate(n, hint);
	}

	static void deallocate(allocator_type alloc, pointer p, size_type n) {
		alloc.deallocate(p, n);
	}

	static void construct(allocator_type alloc, pointer p, const_reference val) {
		alloc.construct(p, val);
	}

	static void destroy(allocator_type& alloc, pointer p) {
		alloc.destroy(p);
	}

	static size_type max_size (allocator_type& alloc) {
		return alloc.max_size();
	}
};

}

#endif /* ALLOCATOR_TRAITS_HPP */
