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
/* Member Types */
private:
	class value_comp;
public:

	typedef Key											key_type;
	typedef T											mapped_type;
	typedef ft::pair<const key_type, mapped_type>		value_type;
	typedef Compare										key_compare;
	typedef value_comp									value_compare;
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

public:
/* Constructors / Destructor */

	/* empty */
	explicit map(const key_compare& key = key_compare(),
	const allocator_type& alloc = allocator_type())
	: _val_cmp(key) {}

	/* range */
	template <class InputIterator>
	map(InputIterator first, InputIterator last,
	const key_compare& key = key_compare(),
	const allocator_type& alloc = allocator_type())
	: _val_cmp(key) {}

	/* copy */
	map (const map& x) {}


private:
	value_compare _val_cmp;

};

/*
	value_compare nested class definition
*/
template <class Key, class T, class Compare, class Alloc>
class map<Key,T,Compare,Alloc>::value_comp : public ft::binary_function<Key, T, bool> {
private:
	value_comp() {}

protected:
	Compare comp;

public:
	value_comp (Compare c)
	: comp(c) {}

	value_comp(const value_comp& from)
	: comp(from.comp) {}

	value_comp& operator=(const value_comp& rhs) {
		if (this == &rhs)
			return *this;
		comp = rhs.comp;
		return *this;
	}

	bool operator() (const value_type& x, const value_type& y) const {
		return comp(x.first, y.first);
	}
};

}

#endif /* MAP_HPP */
