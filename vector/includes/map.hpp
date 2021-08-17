#ifndef MAP_HPP
# define MAP_HPP

# include "pair.hpp"
# include "less.hpp"
# include "reverse_iterator.hpp"

# include <memory> // std::allocator

# ifdef __linux__
# include <cstddef> // size_t
# endif /* __linux__ */

namespace ft {

template < class Key,
			class T,
			class Compare = ft::less<Key>,
			class Alloc = std::allocator<ft::pair<const Key, T> > >
class map {
public:
/* Member Types */

	typedef Key											key_type;
	typedef T											mapped_type;
	typedef ft::pair<const key_type, mapped_type>		value_type;
	typedef Compare										key_compare;
	// value_compare = nested function class to compare elements
	typedef Alloc										allocator_type;


	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;

	// iterator
	// const_iterator
	// typedef ft::reverse_iterator<iterator>			reverse_iterator;
	// typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

	// typedef iterator_traits<iterator>::difference_type	difference_type;

	typedef ptrdiff_t difference_type;
	typedef size_t size_type;

private:

};

}

#endif /* MAP_HPP */
