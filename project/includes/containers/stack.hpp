#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft {

template <class T, class Container = ft::vector<T> >
class stack {
public:
/* Public Member Types */

	typedef Container									container_type;
	typedef typename container_type::value_type			value_type;
	typedef typename container_type::size_type			size_type;
	typedef typename container_type::reference			reference;
	typedef typename container_type::const_reference	const_reference;

public:
/* Constructors / Destructor */

	explicit stack(const Container& cont = Container())
	: c(cont) {}

	stack(const stack& other)
	: c(other.c) {}

	~stack() {}

/* Operator */
	stack& operator=(const stack& rhs) {
		if (this == rhs) {
			return *this;
		}
		c = rhs.c;
		return *this;
	}

/* Element Access */
	reference top() {
		return c.back();
	}

	const_reference top() const {
		return c.back();
	}

/* Capacity */
	bool empty() const {
		return c.empty();
	}

	size_type size() const {
		return c.size();
	}

/* Modifiers */
	void push(const value_type& value) {
		c.push_back(value);
	}

	void pop() {
		c.pop_back();
	}


protected:
	container_type c;

};

template< class T, class Container >
bool operator==(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs) {
	return lhs.c == rhs.c;
}

template< class T, class Container >
bool operator!=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs) {
	return lhs != rhs;
}

template< class T, class Container >
bool operator<(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs) {
	return lhs < rhs;
}

template< class T, class Container >
bool operator<=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs) {
	return lhs <= rhs;
}

template< class T, class Container >
bool operator>(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs) {
	return lhs > rhs;
}

template< class T, class Container >
bool operator>=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs) {
	return lhs >= rhs;
}

}

#endif /* STACK_HPP */
