#ifndef UTILS_HPP
# define UTILS_HPP

# include <cstddef>

namespace ft {

template <class InputIterator>
ptrdiff_t distance(InputIterator first, InputIterator last) {

	ptrdiff_t d(0);
	while (first != last) {
		++d;
		++first;
	}
	return d;
}

template <class InputIterator, class OutputIterator>
OutputIterator copy (InputIterator first, InputIterator last, OutputIterator result) {
	while (first != last) {
		*result = *first;
		++first;
		++result;
	}
	return result;
}

template <class InputIterator1, class InputIterator2>
bool equal (InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2) {

	while (first1 != last1) {
		if (*first1 != *first2) {
			return false;
		}
		++first1;
		++first2;
	}
	return true;
}

}


#endif /*  UTILS_HPP */
