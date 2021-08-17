#ifndef GENITERATOR_HPP
# define GENITERATOR_HPP

template <class IteratorTag, typename T>
class GenIterator
	: public ft::iterator<IteratorTag, T>{
public:

	typedef typename ft::iterator<IteratorTag, T>::value_type value_type;
	typedef typename ft::iterator<IteratorTag, T>::difference_type difference_type;
	typedef typename ft::iterator<IteratorTag, T>::pointer pointer;
	typedef typename ft::iterator<IteratorTag, T>::reference reference;
	typedef typename ft::iterator<IteratorTag, T>::iterator_category iterator_category;
	typedef GenIterator<IteratorTag, T> class_type;

public:
	GenIterator()
	: _ptr(NULL) {}

	GenIterator(const GenIterator& from)
	: _ptr(from.base()) {}

	GenIterator(pointer p)
	: _ptr(p) {}

	~GenIterator() {}

	pointer base() const {
		return _ptr;
	}

/* OPERATORS */

/* Input */
	GenIterator& operator=(const GenIterator& rhs) {
		_ptr = rhs.base();
		return *this;
	}

	GenIterator& operator++() {
		++_ptr;
		return *this;
	}

	GenIterator operator++(int) {
		GenIterator temp(*this);
		++_ptr;
		return temp;
	}

	bool operator==(const GenIterator& rhs) const {
		return _ptr == rhs.base();
	}

	bool operator!=(const GenIterator& rhs) const {
		return !(*this == rhs);
	}

	reference operator*() const {
		return *_ptr;
	}

	pointer operator->() const {
		return _ptr;
	}

/* Bidirectional */
	GenIterator& operator--() {
		--_ptr;
		return *this;
	}

	GenIterator operator--(int) {
		GenIterator temp(*this);
		--_ptr;
		return temp;
	}

/* Random Access */

	GenIterator operator+(difference_type n) const {
		return GenIterator(_ptr + n);
	}

	GenIterator operator-(difference_type n) const {
		return GenIterator(_ptr - n);
	}

	GenIterator& operator+=(difference_type n) {
		_ptr += n;
		return *this;
	}

	GenIterator& operator-=(difference_type n) {
		_ptr -= n;
		return *this;
	}

	reference operator[](difference_type n) const {
		return base()[n];
	}



private:
	pointer _ptr;
};

template <class IteratorTag, typename T>
GenIterator<IteratorTag, T> operator+(typename GenIterator<IteratorTag, T>::difference_type lhs,
							const GenIterator<IteratorTag, T>& rhs) {
	return lhs + rhs;
}

template <class Iterator, typename T>
typename GenIterator<Iterator, T>::difference_type operator-(
			const GenIterator<Iterator, T>& lhs,
			const GenIterator<Iterator, T>& rhs) {
	return lhs.base() - rhs.base();
}


template <class Iterator1, typename T1, class Iterator2, typename T2>
bool operator==(const GenIterator<Iterator1, T1>& lhs,
				const GenIterator<Iterator2, T2>& rhs) {
	return lhs.base() == rhs.base();
}
template <class Iterator1, typename T1, class Iterator2, typename T2>
bool operator!=(const GenIterator<Iterator1, T1>& lhs,
				const GenIterator<Iterator2, T2>& rhs) {
	return lhs.base() != rhs.base();
}
template <class Iterator1, typename T1, class Iterator2, typename T2>
bool operator<(const GenIterator<Iterator1, T1>& lhs,
				const GenIterator<Iterator2, T2>& rhs) {
	return lhs.base() < rhs.base();
}
template <class Iterator1, typename T1, class Iterator2, typename T2>
bool operator<=(const GenIterator<Iterator1, T1>& lhs,
				const GenIterator<Iterator2, T2>& rhs) {
	return lhs.base() <= rhs.base();
}
template <class Iterator1, typename T1, class Iterator2, typename T2>
bool operator>(const GenIterator<Iterator1, T1>& lhs,
				const GenIterator<Iterator2, T2>& rhs) {
	return lhs.base() > rhs.base();
}
template <class Iterator1, typename T1, class Iterator2, typename T2>
bool operator>=(const GenIterator<Iterator1, T1>& lhs,
				const GenIterator<Iterator2, T2>& rhs) {
	return lhs.base() >= rhs.base();
}

#endif /* GENITERATOR_HPP */
