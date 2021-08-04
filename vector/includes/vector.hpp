#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "utils.hpp"

# include <memory>
#ifdef __linux__
# include <cstddef>
#endif

namespace ft {

template <typename T, class Allocator = std::allocator<T> >
class vector {
/* Member Types */
public:
	typedef T value_type;
	typedef Allocator allocator_type;
	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::pointer pointer;
	typedef typename allocator_type::const_pointer const_pointer;

	typedef ptrdiff_t difference_type;
	typedef size_t size_type;

public:
/* Constructors/Destructors */
	explicit vector(const allocator_type& alloc = allocator_type())
	: _alloc(alloc), _table(NULL), _capacity(0), _size(0) {}

	explicit vector(size_type n, const value_type& val = value_type(),
				 	const allocator_type& alloc = allocator_type())
	: _alloc(alloc), _capacity(n), _size(n) {
		_table = _alloc.allocate(n);
		for (size_type i(0); i < n; ++i) {
			_alloc.construct(_table + i, val);
		}
	}

	template <class InputIterator>
	vector(InputIterator first, InputIterator last,
			const allocator_type& alloc = allocator_type())
	: _alloc(alloc), _table(NULL), _size(0) {
		reserve(ft::distance(first, last));
		// here we should use copy, own implementation
		while (first != last) {
			_table[_size] = *first;
			++_size;
			++first;
		}
	}

	~vector() {
		for (size_type i(_size); i > 0; --i) {
			_alloc.destroy(_table - i - 1);
		}
		_alloc.deallocate(_table, _capacity);
	}

/* Capacity */

	size_type size() const {
		return _size;
	}

	size_type max_size() const {
		return _alloc.max_size();
	}

	void resize(size_type n, value_type val = value_type()) {
		if (n > capacity()) {
			reserve(n);

		}
		if (n > size()) {
			for (; _size < _capacity; ++_size) {
				_alloc.construct(_table + _size, val);
			}
		} else {
			value_type* temp = _alloc.allocate(n);
			for (size_type i(0); i < n; ++i) {
				temp[i] = _table[i];
			}
			_alloc.deallocate(_table, _size);
			_size = n;
			_table = temp;
			_capacity = n;
		}
	}

	size_type capacity() const {
		return _capacity;
	}

	bool empty() const {
		return size() == 0;
	}

	void reserve(size_type n) {
		if (n <= _capacity)
			return;
		value_type* temp = _alloc.allocate(n);
		_capacity = n;
		for (size_type i(0); i < _size; ++i)
			temp[i] = _table[i];
		if (_table)
			_alloc.deallocate(_table, _size);
		_table = temp;
	}

/* Element access */

	reference operator[](size_type n) {
		return _table[n];
	}

	const_reference operator[](size_type n) const {
		return _table[n];
	}

/* Modifiers */

	void push_back(const value_type& val) {
		if (_size == _capacity) {
			if (_capacity == 0) {
				reserve(1);
			} else {
				reserve(_capacity * 2);
			}
		}
		_table[_size++] = val;
	}

private:

	allocator_type _alloc;
	value_type* _table;
	size_type _capacity;
	size_type _size;

};

}

#endif /* VECTOR_HPP */
