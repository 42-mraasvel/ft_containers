#ifndef IS_ITERATOR_HPP
# define IS_ITERATOR_HPP

namespace ft {

template <typename T>
struct make_type {
	typedef void type;
};

/*
Using overload resolution to test whether the type Iterator has the required typedefs
*/

template <typename Iterator>
struct is_iterator {

	typedef void* isvalid[2];
	typedef void* invalid[1];

	template <typename U>
	static isvalid& test(typename make_type<typename U::difference_type>::type*,
						 typename make_type<typename U::value_type>::type*,
						 typename make_type<typename U::pointer>::type*,
						 typename make_type<typename U::reference>::type*,
						 typename make_type<typename U::iterator_category>::type*);

	template <typename>
	static invalid& test(...);

	static const bool value = sizeof(test<Iterator>(0, 0, 0, 0, 0)) == sizeof(isvalid);
};

template <typename T>
struct is_iterator<T*> {
	static const bool value = true;
};

template <typename T>
struct is_iterator<const T*> {
	static const bool value = true;
};

}

#endif /* IS_ITERATOR_HPP */
