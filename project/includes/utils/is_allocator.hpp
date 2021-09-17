#ifndef IS_ALLOCATOR_HPP
# define IS_ALLOCATOR_HPP

# include "is_iterator.hpp"

/*
Types:
	typedef typename allocator_type::value_type								value_type;
	typedef typename allocator_type::pointer								pointer;
	typedef typename allocator_type::const_ponter							const_pointer;
	typedef typename allocator_type::reference								reference;
	typedef typename allocator_type::const_reference						const_reference;
	typedef typename allocator_type::size_type								size_type;
	typedef typename allocator_type::difference_type						difference_type;
	typedef typename allocator_type::template rebind<value_type>::other		rebind_alloc;
*/

namespace ft {

template <typename Alloc>
struct is_allocator {

	typedef void* isvalid[2];
	typedef void* invalid[1];

	template <typename U>
	static isvalid& test(typename make_type<typename U::value_type>::type*,
						 typename make_type<typename U::difference_type>::type*,
						 typename make_type<typename U::template rebind<typename U::value_type>::other>::type*);

	template <typename>
	static invalid& test(...);

	/* NULL pointers given to test should be equalto the amount of types listed */
	static const bool value = sizeof(test<Alloc>(0, 0, 0)) == sizeof(isvalid);

};

}

#endif /* IS_ALLOCATOR_HPP */
