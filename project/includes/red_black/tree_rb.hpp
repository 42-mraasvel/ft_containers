#ifndef TREE_RED_BLACK_HPP
# define TREE_RED_BLACK_HPP

# include "node_rb.hpp"
# include "iterator_rb.hpp"
# include "reimplemented/pair.hpp"
# include "utils/utils.hpp"

namespace ft {

template <typename T, typename Compare, typename Alloc>
class TreeRB {
public:
/* Member Types */

	typedef IteratorRB<T> iterator;
	typedef IteratorRB<const T> const_iterator;

private:
	typedef Alloc allocator_type;
	typedef Compare value_compare;
	typedef T value_type;
	typedef size_t size_type;

	typedef NodeRB<T> node_type;
	typedef NodeRB<const T> const_node_type;
	typedef typename node_type::node_pointer node_pointer;
	typedef NodeRB<const T>* const_node_pointer;

	typedef typename node_type::color_type color_type;
	static const color_type BLACK = node_type::BLACK;
	static const color_type RED = node_type::RED;

	typedef typename Alloc::template rebind<node_type>::other	allocator_node;

/* Constructors / Destructor */
public:
	TreeRB()
	: _root(NULL), _size(0), _max_ptr(NULL), _min_ptr(NULL) {
		_M_init_end_pointer();
	}

	TreeRB(const value_compare& comp)
	: _root(NULL), _size(0), _compare(comp), _max_ptr(NULL), _min_ptr(NULL) {
		_M_init_end_pointer();
	}

	TreeRB(const TreeRB& from)
	: _root(NULL), _size(0), _compare(from.value_comp()), _max_ptr(NULL), _min_ptr(NULL) {
		_M_init_end_pointer();
		*this = from;
	}

	~TreeRB() {
		clear();
		_M_destroy_node(_end_ptr);
	}

	TreeRB& operator=(const TreeRB& x) {
		if (this == &x) {
			return *this;
		}
		_M_assign(x);
		_M_update_end_pointer();
		return *this;
	}

/* Public Member Functions */

/* Iterators */
	iterator begin() {
		return _M_create_iterator(_min_ptr);
	}

	const_iterator begin() const {
		return _M_create_iterator(_min_ptr);
	}

	iterator end() {
		return _M_create_iterator(_end_ptr);
	}

	const_iterator end() const {
		return _M_create_iterator(_end_ptr);
	}

/* Capacity */
	size_type size() const {
		return _size;
	}

	size_type max_size() const {
		return _alloc.max_size();
	}

/* Modifiers */

	iterator insert(const value_type& val) {
		_M_unset_end_pointer();

		if (_min_ptr && _compare(val, _min_ptr->getValue())) {
			_M_insert(_min_ptr, val);
		} else if (_max_ptr && _compare(_max_ptr->getValue(), val)) {
			_M_insert(_max_ptr, val);
		} else {
			_M_insert(val);
		}

		_M_check_minmax();
		_M_update_end_pointer();
		return _M_create_iterator(_added_node);
	}

	iterator insert(iterator position, const value_type& val) {
		_M_unset_end_pointer();

		node_pointer x = position.base();
		if (_compare(val, x->getValue()) && x->left != NULL) {
			return insert(val);
		} else if (_compare(x->getValue(), val) && x->right != NULL) {
			return insert(val);
		}

		_M_insert(x, val);
		_M_check_minmax();

		_M_update_end_pointer();
		return _M_create_iterator(_added_node);
	}

	void erase(const value_type& val) {
		erase(find(val));
	}

	void erase(iterator position) {

		if (position == end()) {
			return;
		}

		_M_unset_end_pointer();
		node_pointer x = position.base();
		if (x) {
			_M_delete_node(x);
		}

		if (size() == 0) {
			_M_bzero_tree();
		}
		_M_update_end_pointer();
	}

	void swap(TreeRB& x) {
		ft::swap(_root, x._root);
		ft::swap(_size, x._size);
		ft::swap(_max_ptr, x._max_ptr);
		ft::swap(_min_ptr, x._min_ptr);
		ft::swap(_end_ptr, x._end_ptr);
	}

	void clear() {
		_M_unset_end_pointer();
		_M_clear(base());
		_M_bzero_tree();
		_M_reset_end_pointer();
	}

/* Observers */

	value_compare value_comp() const {
		return value_compare(_compare);
	}

/* Operations */

	iterator find(const value_type& val) {
		_M_unset_end_pointer();
		iterator it = _M_create_iterator(_M_find(val));
		_M_update_end_pointer();
		return it;
	}

	const_iterator find(const value_type& val) const {
		return _M_create_iterator(_M_find(val));
	}

	size_type count(const value_type& val) const {
		return find(val) != end() ? 1 : 0;
	}

	iterator lower_bound(const value_type& k) {
		return _M_lower_bound(k);
	}

	const_iterator lower_bound(const value_type& k) const {
		return _M_lower_bound(k);
	}

	iterator upper_bound(const value_type& k) {
		iterator it = _M_lower_bound(k);
		if (_M_equal(*it, k)) {
			++it;
		}
	
		return it;
	}

	const_iterator upper_bound(const value_type& k) const {
		const_iterator it = _M_lower_bound(k);
		if (_M_equal(*it, k)) {
			++it;
		}
	
		return it;
	}

	ft::pair<iterator, iterator> equal_range(const value_type& val) {
		iterator itlow = lower_bound(val);
		iterator itup(itlow);
		if (_M_equal(*itup, val)) {
			++itup;
		}
		return ft::make_pair(itlow, itup);
	}

	ft::pair<const_iterator, const_iterator> equal_range(const value_type& val) const {
		const_iterator itlow = lower_bound(val);
		const_iterator itup(itlow);
		if (_M_equal(*itup, val)) {
			++itup;
		}
		return ft::make_pair(itlow, itup);
	}

private:

	bool _M_equal(const value_type& a, const value_type& b) const {
		return !(_compare(a, b) || _compare(b, a));
	}


private:
/* Utilities */
	node_pointer _M_new_node(const value_type& val) {
		return _M_new_node(val, NULL);
	}

	node_pointer _M_new_node(const value_type& val, node_pointer parent) {
		node_pointer x = _alloc.allocate(1);
		_alloc.construct(x, node_type(val));
		x->parent = parent;
		_added_node = x;
		return x;
	}

	node_pointer _M_convert_const_pointer(const_node_pointer x) {
		return reinterpret_cast<node_pointer> (x);
	}

	iterator _M_convert_const_iterator(const_iterator x) {
		return _M_create_iterator(_M_convert_const_pointer(x.base()));
	}

	void _M_destroy_node(node_pointer x) {
		if (x == _min_ptr) {
			_min_ptr = _M_find_min(base());
		}

		if (x == _max_ptr) {
			_max_ptr = _M_find_max(base());
		}

		_alloc.destroy(x);
		_alloc.deallocate(x, 1);
	}

	void _M_add_size(size_type n) {
		_size += n;
	}

	void _M_sub_size(size_type n) {
		_size -= n;
	}

	node_pointer _M_find_max(node_pointer x) {
		if (x == NULL) {
			return NULL;
		}
		while (x->right) {
			x = x->right;
		}
		return x;
	}

	node_pointer _M_find_min(node_pointer x) {
		if (x == NULL) {
			return NULL;
		}
		while (x->left) {
			x = x->left;
		}
		return x;
	}

	node_pointer _M_find(const value_type& val) {
		node_pointer x = base();
		while (x) {
			if (_compare(val, x->getValue())) {
				x = x->left;
			} else if (_compare(x->getValue(), val)) {
				x = x->right;
			} else {
				return x;
			}
		}

		return NULL;
	}

	node_pointer _M_find(const value_type& val) const {
		node_pointer x = base();
		while (x && x != _end_ptr) {
			if (_compare(val, x->getValue())) {
				x = x->left;
			} else if (_compare(x->getValue(), val)) {
				x = x->right;
			} else {
				return x;
			}
		}
		return NULL;
	}

	iterator _M_lower_bound(const value_type& k) {
		node_pointer x = base();

		while (x && x != _end_ptr) {
			if (_compare(k, x->getValue())) {
				if (x->left == NULL) {
					return _M_create_iterator(x);
				}
				x = x->left;
			} else if (_compare(x->getValue(), k)) {
				if (x->right == NULL) {
					x = x->next();
					return _M_create_iterator(x);
				}
				x = x->right;
			} else {
				return _M_create_iterator(x);
			}
		}

		return end();
	}

	const_iterator _M_lower_bound(const value_type& k) const {
		node_pointer x = base();

		while (x && x != _end_ptr) {
			if (_compare(k, x->getValue())) {
				if (x->left == NULL) {
					return _M_create_iterator(x);
				}
				x = x->left;
			} else if (_compare(x->getValue(), k)) {
				if (x->right == NULL) {
					x = x->next();
					return _M_create_iterator(x);
				}
				x = x->right;
			} else {
				return _M_create_iterator(x);
			}
		}

		return end();
	}

	iterator _M_create_iterator(node_pointer ptr) {
		if (_max_ptr == NULL || ptr == _end_ptr || ptr == NULL) {
			return _M_end_iterator();
		}

		iterator it = iterator(ptr);
		return it;
	}

	const_iterator _M_create_iterator(node_pointer ptr) const {
		if (_max_ptr == NULL || ptr == _end_ptr || ptr == NULL) {
			return _M_end_iterator();
		}

		const_iterator it = iterator(ptr);
		return it;
	}

	iterator _M_end_iterator() {
		return iterator(_end_ptr, true);
	}

	const_iterator _M_end_iterator() const {
		return iterator(_end_ptr, true);
	}

/* Assignation */
	void _M_assign(const TreeRB& rhs) {
		clear();
		_root = _M_assign(rhs._root, rhs, NULL);
		_size = rhs._size;
	}

	node_pointer _M_assign(node_pointer x, const TreeRB& rhs, node_pointer parent) {
		if (x == NULL || x == rhs._end_ptr) {
			return NULL;
		}
		node_pointer copy = _M_copy_node(x, parent);

		if (x == rhs._max_ptr) {
			_max_ptr = copy;
		}

		if (x == rhs._min_ptr) {
			_min_ptr = copy;
		}

		copy->right = _M_assign(x->right, rhs, copy);
		copy->left = _M_assign(x->left, rhs, copy);
		return copy;
	}

	node_pointer _M_copy_node(node_pointer x, node_pointer parent) {
		node_pointer y = _alloc.allocate(1);
		_alloc.construct(y, *x);
		y->parent = parent;
		return y;
	}

/* Red-Black Utils */
	color_type _M_get_color(node_pointer x) {
		if (x == NULL) {
			return BLACK;
		}

		return x->color;
	}

	void _M_check_minmax() {
		if (_min_ptr == NULL || _compare(_added_node->getValue(), _min_ptr->getValue())) {
			_min_ptr = _added_node;
		}

		if (_max_ptr == NULL || _compare(_max_ptr->getValue(), _added_node->getValue())) {
			_max_ptr = _added_node;
		}
	}

/* Rotations */

	void _M_rotate_left(node_pointer x) {
		node_pointer y  = x->right;
		y->parent = x->parent;
		_M_change_parent_link(x, y);
		x->right = y->left;
		if (x->right) {
			x->right->parent = x;
		}
		x->parent = y;
		y->left = x;
	}

	void _M_rotate_right(node_pointer x) {
		node_pointer y = x->left;
		y->parent = x->parent;
		_M_change_parent_link(x, y);
		x->left = y->right;
		if (x->left) {
			x->left->parent = x;
		}
		x->parent = y;
		y->right = x;
	}

	void _M_change_parent_link(node_pointer x, node_pointer replacement) {
		node_pointer parent = x->parent;
		if (parent == NULL) {
			_root = replacement;
		} else if (parent->left == x) {
			parent->left = replacement;
		} else if (parent->right == x) {
			parent->right = replacement;
		}
		if (replacement) {
			replacement->parent = parent;
		}
	}


/* Insertion */

	void _M_insert(node_pointer parent, const value_type& val) {
		if (parent == NULL) {
			_root = _M_new_node(val);
		} else if (_compare(val, parent->getValue())) {
			parent->left = _M_new_node(val, parent);
		} else if (_compare(parent->getValue(), val)) {
			parent->right = _M_new_node(val, parent);
		} else {
			_added_node = parent;
			return;
		}

		_M_add_size(1);
		_M_insert_fix_property(_added_node);
	}

	void _M_insert(const T& val) {
		_M_insert(_M_find_insert_position(val), val);
	}

	/* Return parent of insertion position or node if present */
	node_pointer _M_find_insert_position(const value_type& val) {
		node_pointer node = base();
		node_pointer parent = NULL;

		while (node) {
			parent = node;
			if (_compare(val, node->getValue())) {
				node = node->left;
			} else if (_compare(node->getValue(), val)) {
				node = node->right;
			} else {
				return node;
			}
		}

		return parent;
	}

/* Fixing RB property post-insertion */
	void _M_insert_fix_property(node_pointer x) {
		while (_M_get_color(x->parent) == RED) {
			if (_M_get_color(_M_get_uncle(x)) == RED) {
				_M_insert_case_1(x);
				x = x->parent->parent;
			} else {
				_M_insert_case_23(x);
			}
		}
		_root->color = BLACK;
	}

	void _M_insert_case_1(node_pointer x) {
		x->parent->color = BLACK;
		x->parent->parent->color = RED;
		_M_get_uncle(x)->color = BLACK;
	}

	void _M_insert_case_23(node_pointer x) {
		x = _M_insert_case_2(x);
		x->parent->color = BLACK;
		x->parent->parent->color = RED;
		if (x->parent == x->parent->parent->left) {
			_M_rotate_right(x->parent->parent);
		} else {
			_M_rotate_left(x->parent->parent);
		}
	}

	node_pointer _M_insert_case_2(node_pointer x) {
		node_pointer parent = x->parent;
		if (parent == parent->parent->left && x == parent->right) {
			_M_rotate_left(parent);
		} else if (parent == parent->parent->right && x == parent->left) {
			_M_rotate_right(parent);
		} else {
			return x;
		}

		return parent;
	}

	node_pointer _M_get_uncle(node_pointer x) {
		if (x->parent == x->parent->parent->right) {
			return x->parent->parent->left;
		}

		return x->parent->parent->right;
	}

/* Node Deletion */
	void _M_delete_node(node_pointer x) {

		node_pointer y;
		node_pointer parent;

		if (x->left == NULL) {
			parent = x->parent;
			y = x->right;
			_M_transplant_node(x, x->right);
		} else if (x->right == NULL) {
			y = x->left;
			_M_transplant_node(x, x->left);
		} else {
			node_pointer min = _M_find_min(x->left);
			_M_swap_node(x, min);
			_M_delete_node(x);
			return;
		}

		_M_sub_size(1);
		if (x->color == BLACK && size() > 0) {
			/* Only time a violation can happen */
			if (y == NULL) {
				_M_delete_fix_property(y, parent);
			} else {
				_M_delete_fix_property(y, y->parent);
			}
		}
		_M_destroy_node(x);
	}

	void _M_transplant_node(node_pointer x, node_pointer y) {
		if (x->parent == NULL) {
			_root = y;
		} else if (x == x->parent->left) {
			x->parent->left = y;
		} else {
			x->parent->right = y;
		}

		if (y != NULL) {
			y->parent = x->parent;
		}
	}

/* Node Deletion Property Fix */

	void _M_delete_fix_property(node_pointer y, node_pointer parent) {
		if (_M_get_color(y) == RED || y == _root) {
			y->color = BLACK;
			return;
		}

		if (y == parent->left) {
			_M_delete_fix_property_left(parent);
		} else {
			_M_delete_fix_property_right(parent);
		}
	}

	void _M_delete_fix_property_left(node_pointer parent) {
		node_pointer sibling = parent->right;

		if (_M_get_color(sibling) == RED) {
			// Erase Case 1
			ft::swap(sibling->color, parent->color);
			_M_rotate_left(parent);
			sibling = parent->right;
		}

		if (_M_get_color(sibling->left) == BLACK && _M_get_color(sibling->right) == BLACK) {
			// Erase Case 2
			sibling->color = RED;
			_M_delete_fix_property(parent, parent->parent);
			return;
		}

		if (_M_get_color(sibling->left) == RED && _M_get_color(sibling->right) == BLACK) {
			// Erase Case 3
			ft::swap(sibling->color, sibling->left->color);
			_M_rotate_right(sibling);
			sibling = sibling->parent;
		}

		// Erase Case 4
		ft::swap(sibling->color, sibling->parent->color);
		sibling->right->color = BLACK;
		_M_rotate_left(parent);

	}

	void _M_delete_fix_property_right(node_pointer parent) {
		node_pointer sibling = parent->left;
		if (_M_get_color(sibling) == RED) {
			// Erase Case 1
			ft::swap(sibling->color, parent->color);
			_M_rotate_right(parent);
			sibling = parent->left;
		}

		if (_M_get_color(sibling->left) == BLACK && _M_get_color(sibling->right) == BLACK) {
			// Erase Case 2
			sibling->color = RED;
			_M_delete_fix_property(parent, parent->parent);
			return;
		}

		if (_M_get_color(sibling->right) == RED && _M_get_color(sibling->left) == BLACK) {
			// Erase Case 3
			ft::swap(sibling->color, sibling->right->color);
			_M_rotate_left(sibling);
			sibling = sibling->parent;
		}

		// Erase Case 4
		ft::swap(sibling->color, sibling->parent->color);
		sibling->left->color = BLACK;
		_M_rotate_right(parent);
	}

/* Node Swap Logic */
	void _M_swap_node(node_pointer x, node_pointer y) {
		if (x->parent == y) {
			_M_swap_node(y, x);
		}
		ft::swap(x->parent, y->parent);
		ft::swap(x->left, y->left);
		ft::swap(x->right, y->right);
		ft::swap(x->color, y->color);
		if (x->parent == x) {
			_M_swap_adjust(x, y);
		}
		_M_swap_update_parent_children(x, y);
	}

	void _M_swap_adjust(node_pointer x, node_pointer y) {
		if (y->left == y) {
			y->left = x;
		}
		else if (y->right == y) {
			y->right = x;
		}
		x->parent = y;
	}

	void _M_swap_update_parent_children(node_pointer x, node_pointer y) {
		_M_update_parent(x, y);
		_M_update_parent(y, x);
		_M_child_update_parent(x);
		_M_child_update_parent(y);
	}

	void _M_child_update_parent(node_pointer x) {
		if (x->left) {
			x->left->parent = x;
		}
		if (x->right) {
			x->right->parent = x;
		}
	}

	void _M_update_parent(node_pointer x, node_pointer y) {
		if (x->parent && x->parent != y) {
			if (x->parent->left == y) {
				x->parent->left = x;
			}
			else if (x->parent->right == y) {
				x->parent->right = x;
			}
		} else if (x->parent == NULL) {
			_root = x;
		}
	}


/* Capacity */

	void _M_bzero_tree() {
		_root = NULL;
		_size = 0;

		_added_node = NULL;
		_max_ptr = NULL;
		_min_ptr = NULL;
	}

	void _M_clear(node_pointer x) {
		if (x == NULL) {
			return;
		}

		_M_clear(x->left);
		_M_clear(x->right);
		_M_destroy_node(x);
	}

/* End Pointer Management */
	void _M_init_end_pointer() {
		_end_ptr = _alloc.allocate(1);
		_alloc.construct(_end_ptr, node_type());
		_end_ptr->color = RED;
	}

	void _M_reset_end_pointer() {
		_end_ptr->left = NULL;
	}

	void _M_update_end_pointer() {
		if (_max_ptr) {
			_max_ptr->right = _end_ptr;
		}
		_end_ptr->left = _max_ptr;
	}

	void _M_unset_end_pointer() {
		if (_max_ptr) {
			_max_ptr->right = NULL;
		}
	}

/* Getters */

	node_pointer base() {
		return _root;
	}

	const node_pointer base() const {
		return _root;
	}

public:
	node_pointer _root;
	allocator_node _alloc;
	size_type _size;
	value_compare _compare;

	node_pointer _added_node;
	node_pointer _max_ptr;
	node_pointer _min_ptr;

	node_pointer _end_ptr;

};

}

#endif  /* TREE_RED_BLACK_HPP */
