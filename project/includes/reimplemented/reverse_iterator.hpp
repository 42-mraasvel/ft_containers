#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "iterator_traits.hpp"

namespace ft {

template <class Iterator>
class reverse_iterator {
public:
/* Member Types */
	typedef Iterator iterator_type;
	typedef typename ft::iterator_traits<Iterator>::iterator_category iterator_category;
	typedef typename ft::iterator_traits<Iterator>::value_type value_type;
	typedef typename ft::iterator_traits<Iterator>::difference_type difference_type;
	typedef typename ft::iterator_traits<Iterator>::pointer pointer;
	typedef typename ft::iterator_traits<Iterator>::reference reference;

public:

/* Constructors/Destructors */
	// Default
	reverse_iterator()
	: _base() {}

	// initialization
	explicit reverse_iterator (iterator_type it)
	: _base(it) {}

	// copy 
	template <class Iter>
	reverse_iterator (const reverse_iterator<Iter>& rev_it)
	: _base(rev_it.base()) {}

	~reverse_iterator() {}

/* Assignment Operator */

	reverse_iterator& operator=(const reverse_iterator& rhs) {
		_base = rhs.base();
		return *this;
	}

/* Member Functions */
	iterator_type base() const {
		return _base;
	}

/* Operators */
	reference operator*() const {
		iterator_type tmp(base());
		return *--tmp;
	}

	reverse_iterator operator+(difference_type n) const {
		return reverse_iterator<iterator_type>(_base - n);
	}

	reverse_iterator& operator++() {
		--_base;
		return *this;
	}

	reverse_iterator operator++(int) {
		reverse_iterator temp(*this);
		--_base;
		return temp;
	}

	reverse_iterator& operator+=(difference_type n) {
		_base -= n;
		return *this;
	}

	reverse_iterator operator-(difference_type n) const {
		return reverse_iterator<iterator_type>(_base + n);
	}

	reverse_iterator& operator--() {
		++_base;
		return *this;
	}

	reverse_iterator operator--(int) {
		reverse_iterator temp(*this);
		++_base;
		return temp;
	}

	reverse_iterator& operator-=(difference_type n) {
		_base += n;
		return *this;
	}

	pointer operator->() const {
		return &(operator*());
	}

	reference operator[](difference_type n) const {
		return base()[-n - 1];
	}

private:
	iterator_type _base;
};

/*
Relational operators
*/

template <class Iterator1, class Iterator2>
bool operator==(const reverse_iterator<Iterator1>& lhs,
				const reverse_iterator<Iterator2>& rhs) {
	return lhs.base() == rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator!=(const reverse_iterator<Iterator1>& lhs,
				const reverse_iterator<Iterator2>& rhs) {
	return lhs.base() != rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator<(const reverse_iterator<Iterator1>& lhs,
				const reverse_iterator<Iterator2>& rhs) {
	return lhs.base() < rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator<=(const reverse_iterator<Iterator1>& lhs,
				const reverse_iterator<Iterator2>& rhs) {
	return lhs.base() <= rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator>(const reverse_iterator<Iterator1>& lhs,
				const reverse_iterator<Iterator2>& rhs) {
	return lhs.base() > rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator>=(const reverse_iterator<Iterator1>& lhs,
				const reverse_iterator<Iterator2>& rhs) {
	return lhs.base() >= rhs.base();
}

/*
Other operator overloads
*/

template <class Iterator>
reverse_iterator<Iterator> operator+(
			typename reverse_iterator<Iterator>::difference_type n,
			const reverse_iterator<Iterator>& rev_it) {
	return rev_it + n;
}

template <class Iterator>
typename reverse_iterator<Iterator>::difference_type operator-(
			const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator>& rhs) {
	return rhs.base() - lhs.base();
}

}


#endif /* REVERSE_ITERATOR_HPP */
