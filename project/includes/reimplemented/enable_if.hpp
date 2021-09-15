#ifndef ENABLE_IF_HPP
# define ENABLE_IF_HPP

/*
Used for SFINAE

Compile-time type checking
*/

namespace ft {

template <bool Condition, typename T>
struct enable_if {};

template <typename T>
struct enable_if<true, T> {
	typedef T type;
};

}

#endif /* ENABLE_IF_HPP */
