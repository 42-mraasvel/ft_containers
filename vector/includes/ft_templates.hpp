#ifndef FT_TEMPLATES_HPP
# define FT_TEMPLATES_HPP

namespace ft {

/*
enable_if implementation
*/
template <bool Cond, typename T = void>
struct enable_if {};

template <typename T>
struct enable_if<true, T> {
	typedef T type;
};



}

#endif /* FT_TEMPLATES_HPP */
