#ifndef FAKEALLOCATOR_HPP
# define FAKEALLOCATOR_HPP

# include <memory>
# include <iostream>

// #define allocator_type std::allocator<T>

namespace ft
{

template <class T>
class Alloc : public std::allocator<T> {
public:
/* Member Types */
	typedef T			value_type;
	typedef T*			pointer;
	typedef T&			reference;
	typedef const T*	const_pointer;
	typedef const T&	const_reference;
	typedef size_t		size_type;
	typedef ptrdiff_t	difference_type;

	using std::allocator<T>::rebind;

	typedef std::allocator<T> allocator_type;

public:
/* Constructors/Destructors */
	Alloc() throw()
	: allocator_type() {
		std::cout << "Alloc Constructor" << std::endl;
	}

	Alloc (const Alloc& alloc) throw()
	: allocator_type(alloc) {
		std::cout << "Alloc Copy Constructor" << std::endl;
	}

	template <class U>
	Alloc (const Alloc<U>& alloc) throw()
	: std::allocator<U>(alloc) {
		std::cout << "Alloc Templated Copy Constructor" << std::endl;
	}

	~Alloc() throw() {
		std::cout << "Alloc Destructor" << std::endl;
	}

/* Member Functions */
	pointer address ( reference x ) const {
		std::cout << "ALLOC ADDRESS" << std::endl;
		return allocator_type::address(x);
	}

	const_pointer address ( const_reference x ) const {
		std::cout << "ALLOC CONST ADDRESS" << std::endl;
		return allocator_type::address(x);
	}

	pointer allocate (size_type n, std::allocator<void>::const_pointer hint=0) {
		std::cout << "ALLOC ALLOCATE" << std::endl;
		return allocator_type::allocate(n, hint);
	}

	void deallocate (pointer p, size_type n) {
		std::cout << "ALLOC DEALOCATE" << std::endl;
		return allocator_type::deallocate(p, n);
	}

	size_type max_size() const throw() {
		std::cout << "ALLOC MAX_SIZE" << std::endl;
		return allocator_type::max_size();
	}

	void construct ( pointer p, const_reference val ) {
		std::cout << "ALLOC CONSTRUCT" << std::endl;
		return allocator_type::construct(p, val);
	}

	void destroy (pointer p) {
		std::cout << "ALLOC DESTROY" << std::endl;
		return allocator_type::destroy(p);
	}



};

}



#endif /* FAKEALLOCATOR_HPP */
