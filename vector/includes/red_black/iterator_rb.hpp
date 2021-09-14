#ifndef ITERATOR_RB_HPP
# define ITERATOR_RB_HPP

# include "iterator.hpp"
# include "node_red_black.hpp"

namespace ft {

template <typename T>
class IteratorRB 
	: public ft::iterator<ft::bidirectional_iterator_tag, T> {

public:
	typedef NodeRB<T>* node_pointer;
	typedef NodeRB<const T>* const_node_pointer;

	typedef ft::iterator<ft::bidirectional_iterator_tag, T> parent_t;
	typedef typename parent_t::reference reference;
	typedef const typename parent_t::reference const_reference;
	typedef typename parent_t::pointer pointer;
	typedef const typename parent_t::pointer const_pointer;

	typedef IteratorRB<const T> const_iterator;

/* Constructors / Destructor */
public:
	IteratorRB()
	: _ptr(NULL), _end_reached(false) {}
	IteratorRB(const IteratorRB& from)
	: _ptr(from._ptr), _end_reached(from._end_reached) {}
	~IteratorRB() {}

	IteratorRB(const node_pointer node)
	: _ptr(node), _end_reached(false) {}

	IteratorRB(const node_pointer node, bool end)
	: _ptr(node), _end_reached(end) {}

public:
/* Operators */
	IteratorRB& operator=(const IteratorRB& rhs) {
		if (this == &rhs) {
			return *this;
		}
		_ptr = rhs._ptr;
		_end_reached = rhs._end_reached;
		return *this;
	}

/* Input */
	IteratorRB& operator++() {
		if (_M_is_end()) {
			_ptr = _ptr->right;
			_end_reached = true;
		} else {
			_ptr = _ptr->next();
		}
		return *this;
	}

	IteratorRB operator++(int) {
		IteratorRB temp(*this);
		if (_M_is_end()) {
			_ptr = _ptr->right;
			_end_reached = true;
		} else {
			_ptr = _ptr->next();
		}
		return temp;
	}

	template <typename T1, typename T2>
	friend bool operator==(const IteratorRB<T1>& lhs, const IteratorRB<T2>& rhs);

	reference operator*() {
		return _ptr->value;
	}

	const_reference operator*() const {
		return _ptr->value;
	}

	pointer operator->() {
		return &(_ptr->value);
	}

	const_pointer operator->() const {
		return &(_ptr->value);
	}

/* Bidirectional */
	IteratorRB& operator--() {
		if (_end_reached == true) {
			_ptr = _ptr->left;
			_end_reached = false;
		} else {
			_ptr = _ptr->prev();
		}
		return *this;
	}

	IteratorRB& operator--(int) {
		IteratorRB temp(*this);
		if (_end_reached == true) {
			_ptr = _ptr->left;
			_end_reached = false;
		} else {
			_ptr = _ptr->prev();
		}
		return temp;
	}

	void set_end() {
		_end_reached = true;
	}

	operator const_iterator() const {
		return const_iterator(
			base(),
			_end_reached
		);
	}

	node_pointer base() {
		return _ptr;
	}

	const_node_pointer base() const {
		return reinterpret_cast<const_node_pointer> (_ptr);
	}

private:

	bool _M_is_end() {
		return _ptr->right && _ptr->right->left == _ptr;
	}

/* Private Member Variables */
private:
	node_pointer _ptr;
	bool _end_reached;

};

template <typename T1, typename T2>
bool operator==(const IteratorRB<T1>& lhs, const IteratorRB<T2>& rhs) {
	return lhs.base() == rhs.base()
		&& lhs._end_reached == rhs._end_reached;
}

template <typename T1, typename T2>
bool operator!=(const IteratorRB<T1> lhs, const IteratorRB<T2> rhs) {
	return !(lhs == rhs);
}

}

#endif /* ITERATOR_RB_HPP */
