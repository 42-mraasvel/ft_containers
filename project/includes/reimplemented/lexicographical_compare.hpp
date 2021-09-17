#ifndef LEXICOGRAPHICAL_COMPARE_HPP
# define LEXICOGRAPHICAL_COMPARE_HPP

# include "reimplemented/enable_if.hpp"
# include "utils/is_iterator.hpp"

namespace ft {

/*
lexicographical_compare:
	https://www.cplusplus.com/reference/algorithm/lexicographical_compare/
*/

template <class InputIterator1, class InputIterator2>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
							InputIterator2 first2, InputIterator2 last2,
							typename ft::enable_if<ft::is_iterator<InputIterator1>::value, bool>::type = true,
							typename ft::enable_if<ft::is_iterator<InputIterator2>::value, bool>::type = true) {

	while (first1 != last1) {

		if (first2 == last2 || *first2 < *first1)
			return false;
		else if (*first1 < *first2)
			return true;
		++first1;
		++first2;
	}
	return first2 != last2;
}

template <class InputIterator1, class InputIterator2, class Compare>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
							InputIterator2 first2, InputIterator2 last2,
							Compare comp,
							typename ft::enable_if<ft::is_iterator<InputIterator1>::value, bool>::type = true,
							typename ft::enable_if<ft::is_iterator<InputIterator2>::value, bool>::type = true) {

	while (first1 != last1) {

		if (first2 == last2 || comp(*first2, *first1))
			return false;
		else if (comp(*first1, *first2))
			return true;
		++first1;
		++first2;
	}
	return first2 != last2;
}

}

#endif /* LEXICOGRAPHICAL_COMPARE_HPP */
