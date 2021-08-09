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

template <typename T>
void swap (T& a, T& b) {
	const T tmp(a);
	a = b;
	b = tmp;
}

}


#endif /*  UTILS_HPP */
