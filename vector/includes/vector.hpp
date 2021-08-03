#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <cstddef>

namespace ft {

template <typename T, class Allocator = std::allocator<T> >
class vector {
/* Member Types */
public:
	typedef T value_type;
	typedef Allocator allocator_type;
	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::pointer pointer;
	typedef typename allocator_type::const_pointer const_pointer;

	typedef ptrdiff_t difference_type;
	typedef size_t size_type;

public:
/* Constructors/Destructors */
	explicit vector(const allocator_type& alloc = allocator_type())
	: _alloc(alloc),
	_table(NULL),
	_capacity(0),
	_size(0) {}

	explicit vector(size_type n, const value_type& val = value_type(),
				 	const allocator_type& alloc = allocator_type())
	: _alloc(alloc),
	_capacity(n),
	_size(n) {
		_table = _alloc.allocate(n);
		for (size_type i(0); i < n; ++i) {
			_alloc.construct(_table + i, val);
		}
	}

	~vector() {
		for (size_type i(_size); i > 0; --i) {
			_alloc.destroy(_table - i - 1);
		}
		_alloc.deallocate(_table, _capacity);
	}


private:

	allocator_type _alloc;
	value_type* _table;
	size_type _capacity;
	size_type _size;

};

}

#endif /* VECTOR_HPP */
