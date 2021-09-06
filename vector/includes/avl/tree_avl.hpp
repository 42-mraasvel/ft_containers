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
	typedef const iterator const_iterator;

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
	TreeAVL(const TreeAVL& from) {}

	~TreeAVL() {
		clear();
	}

/* Operators */
	TreeAVL& operator=(const TreeAVL& rhs) {
		return *this;
	}

/* Public Member Functions */
	node_pointer insert(const value_type& val) {
		_root = _M_insert(_root, val, NULL);
		_M_check_min_max();
		return _node_last_changed;
	}

	size_type erase(const value_type& val) {
		size_type old_size = size();

		return old_size - size();
	}

	size_type size() const {
		return _size;
	}

	size_type max_size() const {
		return _alloc.max_size();
	}

	void clear() {
		_M_clear_tree(_root);
		_root = NULL;
		_size = 0;
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

/* Private Member Functions */
private:
	node_pointer _M_new_node(const value_type& val) {
		node_pointer node = _alloc.allocate(1);
		_alloc.construct(node, node_type(val));
		return node;
	}

	node_pointer _M_new_node_update_tree(const value_type& val, node_pointer parent) {
		_node_last_changed = _M_new_node(val);
		_node_last_changed->parent = parent;
		_M_size_add(1);
		return _node_last_changed;
	}

	iterator _M_create_iterator(node_pointer ptr) {
		return iterator(ptr, _max_ptr);
	}

/* Utils */

	void _M_size_add(size_type n) {
		_size += n;
	}

	void _M_check_min_max() {
		if (_min_ptr == NULL || _compare(_node_last_changed->key, _min_ptr->key)) {
			_min_ptr = _node_last_changed;
		}

		if (_max_ptr == NULL || _compare(_max_ptr->key, _node_last_changed->key)) {
			_max_ptr = _node_last_changed;
		}
	}

/*
AVL insertion
	Complexity: O(n log n)
	1. BST insert: O (n log n)
	2. Preserve AVL property: O(1)
	return: iterator to new node (or node if val was already present)
*/

	node_pointer _M_insert(node_pointer node, const value_type& val, node_pointer parent) {
		if (node == NULL)
			return _M_new_node_update_tree(val, parent);

		if (_compare(val, node->key)) {
			node->left = _M_insert(node->left, val, node);
		}
		else if (_compare(node->key, val)) {
			node->right = _M_insert(node->right, val, node);
		}
		else {
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
		}
		else if (balance < -1) {
			if (node->right->get_balance() > 0) {
				_M_rotate_right(node->right);
			}
			_M_rotate_left(node);
		}
		else {
			return node;
		}
		return node->parent;
	}

	void _M_rotate_left(node_pointer x) {
		node_pointer y  = x->right;
		y->parent = x->parent;
		if (y->parent == NULL) {
			_root = y;
		}
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
		if (y->parent == NULL)
			_root = y;
		x->left = y->right;
		if (x->left)
			x->left->parent = x;
		x->parent = y;
		y->right = x;
		x->update_height();
		y->update_height();
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
