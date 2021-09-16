#ifndef FAKEITERATOR_HPP
# define FAKEITERATOR_HPP

# include <cstddef>
# include <iterator>

template <typename T>
class FakeIterator {

public:
/* MEMBER TYPES */
	typedef ptrdiff_t							difference_type;
	typedef T									value_type;
	typedef T*									pointer;
	typedef T&									reference;
	typedef std::random_access_iterator_tag		iterator_category;

public:
/* ALL CATEGORIES */

	FakeIterator(const FakeIterator& from)
	: ptr(from.base()) {}

	~FakeIterator() {}

	FakeIterator& operator=(const FakeIterator& rhs) {
		if (this == &rhs) {
			return *this;
		}
		ptr = rhs.base();
		return *this;
	}

	FakeIterator& operator++() {
		++ptr;
		return *this;
	}

	FakeIterator operator++(int) {
		FakeIterator temp(*this);
		ptr++;
		return temp;
	}

/* INPUT ITERATOR */
	T& operator*() const {
		return *ptr;
	}

	T* operator->() const {
		return &(*ptr);
	}

/* FORWARD ITERATOR */
	FakeIterator() {}

/* BIDIRECTIONAL ITERATOR */
	FakeIterator& operator--() {
		--ptr;
		return *this;
	}

	FakeIterator operator--(int) {
		FakeIterator temp(*this);
		--ptr;
		return temp;
	}

/* RANDOM ACCESS ITERATOR */
	FakeIterator operator+(ptrdiff_t n) const {
		return FakeIterator(base() + n);
	}

	FakeIterator operator-(ptrdiff_t n) const {
		return FakeIterator(base() - n);
	}

	FakeIterator& operator+=(ptrdiff_t n) {
		ptr += n;
		return *this;
	}

	FakeIterator& operator-=(ptrdiff_t n) {
		ptr -= n;
		return *this;
	}

	ptrdiff_t operator-(const FakeIterator& rhs) const {
		return base() - rhs.base();
	}

	T& operator[](ptrdiff_t n) const{
		return base()[n];
	}

	T* base() const {
		return ptr;
	}

public:
	FakeIterator(T* x)
	: ptr(x) {}

private:
	T* ptr;

};

/* INPUT ITERATOR */
template <typename T1, typename T2>
bool operator==(FakeIterator<T1> lhs, FakeIterator<T2> rhs) {
	return lhs.base() == rhs.base();
}

template <typename T1, typename T2>
bool operator!=(FakeIterator<T1> lhs, FakeIterator<T2> rhs) {
	return lhs.base() == rhs.base();
}

/* RANDOM ACCESS ITERATOR */
template <typename T1, typename T2>
bool operator<(FakeIterator<T1> lhs, FakeIterator<T2> rhs) {
	return lhs.base() < rhs.base();
}

template <typename T1, typename T2>
bool operator>(FakeIterator<T1> lhs, FakeIterator<T2> rhs) {
	return lhs.base() > rhs.base();
}

template <typename T1, typename T2>
bool operator<=(FakeIterator<T1> lhs, FakeIterator<T2> rhs) {
	return lhs.base() <= rhs.base();
}

template <typename T1, typename T2>
bool operator>=(FakeIterator<T1> lhs, FakeIterator<T2> rhs) {
	return lhs.base() >= rhs.base();
}

#endif /* FAKEITERATOR_HPP */
