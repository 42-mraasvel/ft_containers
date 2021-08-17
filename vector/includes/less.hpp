#ifndef LESS_HPP
# define LESS_HPP

namespace ft {

template <class T>
struct less {
	bool operator() (const T& x, const T& y) {
		return x < y;
	}
};

}

#endif /* LESS_HPP */
