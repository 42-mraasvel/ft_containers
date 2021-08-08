#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "iterator_traits.hpp"
# include "utils.hpp"

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

/* Member Functions */
	iterator_type base() const {
		return _base;
	}

/* Operators */
	reference operator*() const {
		return base()[-1];
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

}


#endif /* REVERSE_ITERATOR_HPP */
