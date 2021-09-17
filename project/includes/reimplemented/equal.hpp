#ifndef EQUAL_HPP
# define EQUAL_HPP

# include "reimplemented/enable_if.hpp"
# include "utils/is_iterator.hpp"

namespace ft {

/*
equal:
	https://www.cplusplus.com/reference/algorithm/equal/
*/

template <class InputIterator1, class InputIterator2>
bool equal(InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2,
			typename ft::enable_if<ft::is_iterator<InputIterator1>::value, bool>::type = true,
			typename ft::enable_if<ft::is_iterator<InputIterator2>::value, bool>::type = true) {

	while (first1 != last1) {
		if (*first1 != *first2)
			return false;
		++first2;
		++first1;
	}
	return true;
}

template <class InputIterator1, class InputIterator2, class BinaryPredicate>
bool equal(InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, BinaryPredicate pred,
			typename ft::enable_if<ft::is_iterator<InputIterator1>::value, bool>::type = true,
			typename ft::enable_if<ft::is_iterator<InputIterator2>::value, bool>::type = true) {

	while (first1 != last1) {
		if (!pred(*first1, *first2))
			return false;
		++first1;
		++first2;
	}
	return true;
}

}

#endif /* EQUAL_HPP */
