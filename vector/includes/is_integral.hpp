#ifndef IS_INTEGRAL_HPP
# define IS_INTEGRAL_HPP

namespace ft {

/* Integral_constant: bool specializations */

template <class T, T v>
struct integral_constant {
	typedef T value_type;
	typedef integral_constant<T, v> type;

	static const T value = v;

	operator T() {
		return v;
	}
};

typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;

/* remove_cv (const/volatile) specializations */

template <class T>
struct remove_cv {
	typedef T type;
};

template <class T>
struct remove_cv<const T> {
	typedef T type;
};

template <class T>
struct remove_cv<volatile T> {
	typedef T type;
};

/* is_integral base versions */

template <class T>
struct is_integral_base : public ft::false_type {};

template <> struct is_integral_base <bool>					: public ft::true_type {};
template <> struct is_integral_base <char>					: public ft::true_type {};
template <> struct is_integral_base <wchar_t>				: public ft::true_type {};
template <> struct is_integral_base <signed char>			: public ft::true_type {};
template <> struct is_integral_base <short>					: public ft::true_type {};
template <> struct is_integral_base <int>					: public ft::true_type {};
template <> struct is_integral_base <long>					: public ft::true_type {};
template <> struct is_integral_base <unsigned char>			: public ft::true_type {};
template <> struct is_integral_base <unsigned short>		: public ft::true_type {};
template <> struct is_integral_base <unsigned int>			: public ft::true_type {};
template <> struct is_integral_base <unsigned long>			: public ft::true_type {};

/* C++ 11 extension data types */

// template <> struct is_integral_base <char16_t>				: public ft::true_type {};
// template <> struct is_integral_base <char32_t>				: public ft::true_type {};
// template <> struct is_integral_base <long long int>				: public ft::true_type {};
// template <> struct is_integral_base <unsigned long long>	: public ft::true_type {};


/* Actual is_integral implementation */

template <class T>
struct is_integral
	: public ft::is_integral_base<typename ft::remove_cv<T>::type>
{};

}

#endif /* IS_INTEGRAL_HPP */
