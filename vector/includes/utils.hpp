#ifndef UTILS_HPP
# define UTILS_HPP

# include <cstddef>
# include "is_integral.hpp"
# include <memory>

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

template <class InputIterator, class OutputIterator, class Alloc>
OutputIterator copy(InputIterator first, InputIterator last,
					OutputIterator result, Alloc& alloc) {

	while (first != last) {
		alloc.construct(result, *first);
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

/*
type_cmp<a, b>::value evaluates to true if types are equal, otherwise false

Removes const/volatile qualifiers from types
*/
template <typename T1, typename T2>
struct type_cmp_base : public ft::false_type {};

template <typename T>
struct type_cmp_base<T, T> : public ft::true_type {};

template <typename T1, typename T2>
struct type_cmp :
	public type_cmp_base<
			typename ft::remove_cv<T1>::type,
			typename ft::remove_cv<T2>::type> {};

}


#endif /*  UTILS_HPP */
