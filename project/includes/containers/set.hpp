#ifndef SET_HPP
# define SET_HPP

# include "utils/less.hpp"
# include "utils/is_allocator.hpp"
# include "utils/is_same.hpp"
# include "red_black/tree_rb.hpp"
# include "reimplemented/reverse_iterator.hpp"
# include "reimplemented/equal.hpp"
# include "reimplemented/lexicographical_compare.hpp"
# include "reimplemented/enable_if.hpp"

namespace ft {

template <class T,
		class Compare = ft::less<T>,
		class Alloc = std::allocator<T> >
class set {

private:
	typedef ft::TreeRB<const T, Compare, Alloc> tree_type;
public:
/* Public Member Types */
	typedef T key_type;
	typedef T value_type;
	typedef Compare key_compare;
	typedef Compare value_compare;
	typedef Alloc allocator_type;

	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::pointer pointer;
	typedef typename allocator_type::const_pointer const_pointer;

	/* Iterators */

	typedef typename tree_type::iterator iterator;
	typedef typename tree_type::iterator const_iterator;
	typedef ft::reverse_iterator<iterator> reverse_iterator;
	typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

	typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
	typedef size_t size_type;

public:
/* Public Member Functions */

/* Constructors/Destructor */
	explicit set(const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<ft::is_allocator<allocator_type>::value, bool>::type = true,
				typename ft::enable_if<ft::is_same<value_type, typename allocator_type::value_type>::value, bool>::type = true)
	: _tree(comp), _alloc(alloc) {
	}

	template <class InputIterator>
	set(InputIterator first, InputIterator last,
		const key_compare& comp = key_compare(),
		const allocator_type& alloc = allocator_type(),
		typename ft::enable_if<ft::is_iterator<InputIterator>::value, bool>::type = true,
		typename ft::enable_if<ft::is_allocator<allocator_type>::value, bool>::type = true,
		typename ft::enable_if<ft::is_same<value_type, typename allocator_type::value_type>::value, bool>::type = true)
	: _tree(comp), _alloc(alloc) {
		insert(first, last);
	}

	set(const set& x)
	: _tree(x._tree) {}

	~set() {}

/* Operators */
	set& operator=(const set& rhs) {
		_tree = rhs._tree;
		return *this;
	}

/* Iterators */
	iterator begin() {
		return _tree.begin();
	}

	const_iterator begin() const {
		return _tree.begin();
	}

	iterator end() {
		return _tree.end();
	}

	const_iterator end() const {
		return _tree.end();
	}

	reverse_iterator rbegin() {
		return reverse_iterator(end());
	}

	const_reverse_iterator rbegin() const {
		return const_reverse_iterator(end());
	}

	reverse_iterator rend() {
		return reverse_iterator(begin());
	}

	const_reverse_iterator rend() const {
		return const_reverse_iterator(begin());
	}

/* Capacity */
	bool empty() const {
		return size() == 0;
	}

	size_type size() const {
		return _tree.size();
	}

	size_type max_size() const {
		return _tree.max_size();
	}

/* Modifiers */
	ft::pair<iterator, bool> insert(const value_type& val) {
		size_type old_size = size();
		iterator it = _tree.insert(val);
		return ft::make_pair(it, old_size > size());
	}

	iterator insert(iterator position, const value_type& val) {
		(void)position;
		return _tree.insert(val);
	}

	template <class InputIterator>
	void insert(InputIterator first, InputIterator last,
				typename ft::enable_if< ft::is_iterator<InputIterator>::value, bool>::type = true) {
		while (first != last) {
			_tree.insert(*first);
			++first;
		}
	}

	void erase(iterator position) {
		return _tree.erase(position);
	}

	size_type erase(const value_type& val) {
		size_type old_size = size();
		_tree.erase(val);
		return (old_size - size());
	}

	void erase(iterator first, iterator last) {
		while (first != last) {
			_tree.erase(first++);
		}
	}

	void swap(set& x) {
		_tree.swap(x._tree);
	}

	void clear() {
		_tree.clear();
	}

/* Observers */
	key_compare key_comp() const {
		return _tree.value_comp();
	}

	value_compare value_comp() const {
		return _tree.value_comp();
	}

/* Operations */
	iterator find(const value_type& val) const {
		return _tree.find(val);
	}

	size_type count(const value_type& val) const {
		return _tree.count(val);
	}

	iterator lower_bound(const value_type& val) const {
		return _tree.lower_bound(val);
	}

	iterator upper_bound(const value_type& val) const {
		return _tree.upper_bound(val);
	}

	ft::pair<iterator, iterator> equal_range(const value_type& val) const {
		return _tree.equal_range(val);
	}

/* Allocator */
	allocator_type get_allocator() const {
		return _alloc;
	}

public:
/* Private Member Variables */
	tree_type _tree;
	allocator_type _alloc;
};

template <class T, class Compare, class Alloc>
void swap(ft::set<T, Compare, Alloc>& lhs,
		ft::set<T, Compare, Alloc>& rhs) {
	lhs.swap(rhs);
}

/* Comparison Operators */

template< class Key, class Compare, class Alloc >
bool operator==(const ft::set<Key,Compare,Alloc>& lhs,
				const ft::set<Key,Compare,Alloc>& rhs ) {
	if (lhs.size() != rhs.size()) {
		return false;
	}

	return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}
template< class Key, class Compare, class Alloc >
bool operator!=(const ft::set<Key,Compare,Alloc>& lhs,
				const ft::set<Key,Compare,Alloc>& rhs) {
	return !(lhs == rhs);
}
template< class Key, class Compare, class Alloc >
bool operator<( const ft::set<Key,Compare,Alloc>& lhs,
				const ft::set<Key,Compare,Alloc>& rhs) {
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}
template< class Key, class Compare, class Alloc >
bool operator<=(const ft::set<Key,Compare,Alloc>& lhs,
				const ft::set<Key,Compare,Alloc>& rhs) {
	return !(rhs < lhs);
}
template< class Key, class Compare, class Alloc >
bool operator>( const ft::set<Key,Compare,Alloc>& lhs,
				const ft::set<Key,Compare,Alloc>& rhs) {
	return rhs < lhs;
}
template< class Key, class Compare, class Alloc >
bool operator>=(const ft::set<Key,Compare,Alloc>& lhs,
				const ft::set<Key,Compare,Alloc>& rhs) {
	return !(lhs < rhs);
}

}

#endif /* SET_HPP */
