#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

# include "iterator.hpp"

namespace ft {

template <class Iterator>
class iterator_traits {
public:
	typedef typename Iterator::iterator_category iterator_category;
	typedef typename Iterator::value_type        value_type;
	typedef typename Iterator::difference_type   difference_type;
	typedef typename Iterator::pointer           pointer;
	typedef typename Iterator::reference         reference;
};

/*
pointer specialization
*/
template <class T>
class iterator_traits<T*> {
public:
/* Member Types */
	typedef ptrdiff_t difference_type;
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	typedef ft::random_access_iterator_tag iterator_category;
};


/*
const pointer specialization
*/
template <class T>
class iterator_traits<const T*> {
public:
/* Member Types */
	typedef ptrdiff_t difference_type;
	typedef T value_type;
	typedef const T* pointer;
	typedef const T& reference;
	typedef ft::random_access_iterator_tag iterator_category;
};

template <typename Iterator>
typename ft::iterator_traits<Iterator>::iterator_category
_iterator_category(Iterator) {
	return typename ft::iterator_traits<Iterator>::iterator_category();
}

}

#endif /* ITERATOR_TRAITS_HPP */
