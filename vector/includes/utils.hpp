#ifndef UTILS_HPP
# define UTILS_HPP

# include <cstddef>
# include "is_integral.hpp"
# include "distance.hpp"
# include "is_signed.hpp"
# include <memory>

namespace ft {

template <class InputIterator, class OutputIterator>
OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result) {
	while (first != last) {
		*result = *first;
		++first;
		++result;
	}
	return result;
}

template <class BidirectionalIterator1, class BidirectionalIterator2>
BidirectionalIterator2 copy_backward(BidirectionalIterator1 first,
									BidirectionalIterator1 last,
									BidirectionalIterator2 result) {
	while (last != first) {
		--result;
		--last;
		*result = *last;
	}
	return result;
}

template <class ValueType, class OutputIterator, class Alloc>
OutputIterator construct_uninitialized(size_t n, const ValueType& val,
									OutputIterator result, Alloc& alloc) {
	for (size_t i = 0; i < n; ++i) {
		alloc.construct(&(*result), val);
		++result;
	}
	return result;
}

template <class InputIterator, class OutputIterator, class Alloc>
OutputIterator copy_uninitialized(InputIterator first, InputIterator last,
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

template <typename T>
const T& max(const T& a, const T& b) {
	return a > b ? a : b;
}

template <typename T, \
typename = typename ft::enable_if<ft::is_signed<T>::value, bool>::type>
T abs(const T& a) {
	if (a < 0)
		return -a;
	return a;
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
