#ifndef TREE_AVL_HPP
# define TREE_AVL_HPP

# include "node_avl.hpp"
# include "iterator_avl.hpp"

# include <cstddef>

namespace ft {

template <typename T, typename Compare, typename Alloc>
class TreeAVL {
/* Member Types */
public:
	typedef T															value_type;
	typedef size_t														size_type;
	typedef NodeAVL<T>													node_type;

	typedef Compare														value_compare;

	typedef Alloc														allocator_type;
	typedef typename allocator_type::template rebind<node_type>::other	allocator_node;

	typedef typename allocator_node::pointer							node_pointer;
	typedef typename allocator_node::const_pointer						const_node_pointer;
	typedef typename allocator_node::pointer							node_reference;
	typedef typename allocator_node::const_pointer						const_node_reference;

	typedef IteratorAVL<T> iterator;
	typedef IteratorAVL<const T> const_iterator;

	typedef bool (TreeAVL::*compare_fnc_t)(const value_type&, const value_type&);

/*


************ TESTING PURPOSES, REMOVE ON TURNIN **********

*/
public:
	node_pointer root() {
		return _root;
	}

	node_pointer max() {
		return _max_ptr;
	}

	node_pointer min() {
		return _min_ptr;
	}

/* Constructors / Destructor */
private:
	TreeAVL()
	: _root(NULL), _size(0) {}
public:
	TreeAVL(const Compare& c)
	: _root(NULL), _compare(c), _size(0), _min_ptr(NULL), _max_ptr(NULL) {}
	TreeAVL(const TreeAVL& from)
	: _alloc(from._alloc), _compare(from._compare), _size(0) {
		_M_assign(from);
	}

	~TreeAVL() {
		clear();
	}

/* Operators */
	TreeAVL& operator=(const TreeAVL& rhs) {
		if (this == &rhs) {
			return *this;
		}
		clear();
		_M_assign(rhs);
		return *this;
	}

/* Public Member Functions */


	size_type size() const {
		return _size;
	}

	size_type max_size() const {
		return _alloc.max_size();
	}

	void clear() {
		_M_clear_tree(_root);
		_M_bzero_tree();
	}

/* Iterators */
	iterator begin() {
		return _M_create_iterator(_min_ptr);
	}

	const_iterator begin() const {
		return _M_create_iterator(_min_ptr);
	}

	iterator end() {
		return _M_create_iterator(NULL);
	}

	const_iterator end() const {
		return _M_create_iterator(NULL);
	}

/* Modifiers */

	iterator insert(const value_type& val) {
		_root = _M_insert(_root, val, NULL);
		_M_check_min_max();
		return _M_create_iterator(_node_last_changed);
	}

	iterator insert(iterator position, const value_type& val) {
		if (_compare(*position, val) && position.base()->right == NULL) {
			position.base()->right = _M_new_node_update_tree(val, position.base());
			_M_check_min_max();
			_M_update_tree(position.base());
			return _M_create_iterator(_node_last_changed);
		} else {
			return insert(val);
		}
	}

	void erase(iterator position) {
		_M_erase_node(position.base());
	}

	void swap(TreeAVL& x) {
		ft::swap(_root, x._root);
		ft::swap(_size, x._size);
		ft::swap(_node_last_changed, x._node_last_changed);
		ft::swap(_min_ptr, x._min_ptr);
		ft::swap(_max_ptr, x._max_ptr);
	}

/* Observers */

	value_compare comp_object() const {
		return _compare;
	}

/* Operations */

	iterator find(const value_type& v) {
		return _M_find(_root, v);
	}

	const_iterator find(const value_type& v) const {
		return _M_find(_root, v);
	}

	iterator lower_bound(const value_type& k) {
		return _M_find_comp(k, &TreeAVL::greater_or_equal);
	}

	const_iterator lower_bound(const value_type& k) const {
		return _M_find_comp(k, &TreeAVL::greater_or_equal);
	}

	iterator upper_bound(const value_type& k) {
		return _M_find_comp(k, &TreeAVL::greater);
	}

	const_iterator upper_bound(const value_type& k) const {
		return _M_find_comp(k, &TreeAVL::greater);
	}

	bool greater(const value_type& a, const value_type& b) {
		return _compare(b, a);
	}

	bool greater_or_equal(const value_type& a, const value_type& b) {
		return !_compare(a, b);
	}

	bool equal(const value_type& a, const value_type& b) {
		return !(_compare(a, b) && _compare(b, a));
	}

/* Private Member Functions */
private:
	node_pointer _M_new_node(const value_type& val) {
		node_pointer node = _alloc.allocate(1);
		_alloc.construct(node, node_type(val));
		return node;
	}

	node_pointer _M_new_node(const node_type& from) {
		node_pointer node = _alloc.allocate(1);
		_alloc.construct(node, from);
		return node;
	}

	node_pointer _M_new_node_update_tree(const value_type& val, node_pointer parent) {
		_node_last_changed = _M_new_node(val);
		_node_last_changed->parent = parent;
		_M_size_add(1);
		return _node_last_changed;
	}

	iterator _M_create_iterator(node_pointer ptr) {
		iterator it = iterator(ptr, &_max_ptr);
		if (_max_ptr == NULL) {
			it.set_end();
		}
		return it;
	}

	const_iterator _M_create_iterator(node_pointer ptr) const {
		const_iterator it = iterator(ptr, &_max_ptr);
		if (_max_ptr == NULL) {
			it.set_end();
		}
		return it;
	}

/* Utils */
	void _M_size_add(size_type n) {
		_size += n;
	}

	void _M_check_min_max() {
		if (_min_ptr == NULL) {
			_min_ptr = _node_last_changed;
			_max_ptr = _node_last_changed;
		} else if (_compare(_node_last_changed->key, _min_ptr->key)) {
			_min_ptr = _node_last_changed;
		} else if (_compare(_max_ptr->key, _node_last_changed->key)) {
			_max_ptr = _node_last_changed;
		}
	}

	void _M_check_min_max(node_pointer removed) {
		if (_min_ptr == removed) {
			_min_ptr = _M_find_min(_root);
		}
		if (_max_ptr == removed) {
			_max_ptr = _M_find_max(_root);
		}
	}

	void _M_bzero_tree() {
		_root = NULL;
		_min_ptr = NULL;
		_max_ptr = NULL;
		_size = 0;
	}

/*
AVL find
*/

	iterator _M_find(node_pointer node, const value_type& v) {
		if (node == NULL) {
			return end();
		}

		if (_compare(v, node->key)) {
			return _M_find(node->left, v);
		} else if (_compare(node->key, v)) {
			return _M_find(node->right, v);
		}

		return _M_create_iterator(node);
	}

	const_iterator _M_find(node_pointer node, const value_type& v) const {
		if (node == NULL) {
			return end();
		}

		if (_compare(v, node->key)) {
			return _M_find(node->left, v);
		} else if (_compare(node->key, v)) {
			return _M_find(node->right, v);
		}

		return _M_create_iterator(node);
	}

	node_pointer _M_find_min(node_pointer node) {
		if (node == NULL) {
			return NULL;
		}

		while (node->left) {
			node = node->left;
		}

		return node;
	}

	node_pointer _M_find_max(node_pointer node) {
		if (node == NULL) {
			return NULL;
		}

		while (node->right) {
			node = node->right;
		}

		return node;
	}

	iterator _M_find_comp(const value_type& k, compare_fnc_t compare) {
		for (iterator it = begin(); it != end(); ++it) {
			if ((this->*compare)(*it, k)) {
				return it;
			}
		}

		return end();
	}

	const_iterator _M_find_comp(const value_type& k, compare_fnc_t compare) const {
		for (const_iterator it = begin(); it != end(); ++it) {
			if ((this->*compare)(*it, k)) {
				return it;
			}
		}

		return end();
	}

/*
AVL insertion
	Complexity: O(n log n)
	1. BST insert: O (n log n)
	2. Preserve AVL property: O(1)
	return: iterator to new node (or node if val was already present)
*/

	node_pointer _M_insert(node_pointer node, const value_type& val, node_pointer parent) {
		if (node == NULL) {
			return _M_new_node_update_tree(val, parent);
		}

		if (_compare(val, node->key)) {
			node->left = _M_insert(node->left, val, node);
		} else if (_compare(node->key, val)) {
			node->right = _M_insert(node->right, val, node);
		} else {
			_node_last_changed = node;
			return node;
		}

		node->update_height();
		return _M_check_balance(node);
	}


/*
AVL Rotations
	Rebalance tree using rotations when abs(balance) > 1
	Complexity: O(1) pointer swaps
Resource:
	https://www.youtube.com/watch?v=FNeL18KsWPc
*/
	node_pointer _M_check_balance(node_pointer node) {
		int balance = node->get_balance();
		if (balance > 1) {
			if (node->left->get_balance() < 0) {
				_M_rotate_left(node->left);
			}
			_M_rotate_right(node);
		} else if (balance < -1) {
			if (node->right->get_balance() > 0) {
				_M_rotate_right(node->right);
			}
			_M_rotate_left(node);
		} else {
			return node;
		}
		return node->parent;
	}

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
		x->update_height();
		y->update_height();
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
		x->update_height();
		y->update_height();
	}

/*
AVL node deletion
*/

	void _M_erase_node(node_pointer x) {

		if (x->left && x->right) {
			node_pointer replacement = x->prev();
			node_type::swap(x, replacement);
			if (replacement->parent == NULL) {
				_root = replacement;
			}
			_M_erase_node(x);
			return;
		} else if (x->left) {
			_M_change_parent_link(x, x->left);
		} else if (x->right) {
			_M_change_parent_link(x, x->right);
		} else {
			_M_change_parent_link(x, NULL);
		}

		node_pointer parent = x->parent;
		_M_check_min_max(x);
		_M_delete_node(x);
		_size -= 1;

		if (parent) {
			_M_update_tree(parent);
		} else if (size() == 0) {
			_M_bzero_tree();
		}
	}

	void _M_update_tree(node_pointer x) {
		while (x) {
			x->update_height();
			x = _M_check_balance(x);
			x = x->parent;
		}
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

/*
Assignation
*/

	void _M_assign(const TreeAVL& rhs) {
		_root = _M_copy_node(rhs._root, NULL, rhs);
		_size = rhs.size();
		_compare = rhs._compare;
	}

	node_pointer _M_copy_node(const_node_pointer node, node_pointer parent, const TreeAVL& from) {
		if (node == NULL) {
			return NULL;
		}
		node_pointer copy = _M_new_node(*node);
		copy->parent = parent;
		copy->left = _M_copy_node(node->left, copy, from);
		copy->right = _M_copy_node(node->right, copy, from);
		if (node == from._min_ptr) {
			_min_ptr = copy;
		}
		if (node == from._max_ptr) {
			_max_ptr = copy;
		}
		return copy;
	}

/*
Clean up, deletion
*/

	void _M_clear_tree(node_pointer node) {
		if (node == NULL)
			return;
		_M_clear_tree(node->left);
		_M_clear_tree(node->right);
		_M_delete_node(node);
	}

	void _M_delete_node(node_pointer node) {
		_alloc.destroy(node);
		_alloc.deallocate(node, 1);
	}

/* Private Member Variables */
private:
	node_pointer _root;
	allocator_node _alloc;
	value_compare _compare;
	size_type _size;

	node_pointer _node_last_changed;
	node_pointer _min_ptr;
	node_pointer _max_ptr;

};

}

#endif /* TREE_AVL_HPP */
