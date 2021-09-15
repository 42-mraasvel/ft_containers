#ifndef NODE_RED_BLACK_HPP
# define NODE_RED_BLACK_HPP

# include <cstddef>

namespace ft {

template <typename T>
class NodeRB {

public:

	typedef bool color_type;

	static const color_type RED = true;
	static const color_type BLACK = false;

	typedef T value_type;
	typedef NodeRB node_type;
	typedef node_type* node_pointer;
	typedef const node_type* const_node_pointer;

public:

	NodeRB()
	: left(NULL), right(NULL), parent(NULL), color(RED), value() {}

	NodeRB(const value_type& val)
	: left(NULL), right(NULL), parent(NULL), color(RED), value(val) {}

	NodeRB(const value_type& val, node_pointer parent)
	: left(NULL), right(NULL), parent(parent), color(RED), value(val) {}

	NodeRB(const NodeRB& rhs)
	: left(NULL), right(NULL), parent(NULL), color(rhs.color), value(rhs.value) {}

	~NodeRB() {}

	NodeRB& operator=(const NodeRB& rhs) {
		if (this == &rhs) {
			return *this;
		}
		color = rhs.color;
		value = rhs.getValue();
		return *this;
	}

	const value_type& getValue() const {
		return value;
	}

/* Iterating */
	node_pointer next() {
		if (right) {
			return _M_find_min(right);
		} else if (parent && parent->left == static_cast<void*>(this)) {
			return parent;
		}
		return _M_next_node(parent);
	}

	const node_pointer next() const {
		if (right) {
			return _M_find_min(right);
		} else if (parent && parent->left == static_cast<void*>(this)) {
			return parent;
		}
		return _M_next_node(parent);
	}

	node_pointer prev() {
		if (left) {
			return _M_find_max(left);
		} else if (parent && parent->right == static_cast<void*>(this)) {
			return parent;
		}
		return _M_prev_node(parent);
	}

	const node_pointer prev() const {
		if (left) {
			return _M_find_max(left);
		} else if (parent && parent->right == static_cast<void *>(this)) {
			return parent;
		}
		return _M_prev_node(parent);
	}

private:
	node_pointer _M_next_node(node_pointer node) {
		const_node_pointer prev = NULL;
		while (node) {
			if (_M_node_equal(node->left, prev)) {
				return node;
			}
			prev = node;
			node = node->parent;
		}
		return NULL;
	}

	node_pointer _M_prev_node(node_pointer node) {
		const_node_pointer prev = NULL;
		while (node) {
			if (_M_node_equal(node->right, prev)) {
				return node;
			}
			prev = node;
			node = node->parent;
		}
		return NULL;
	}

	bool _M_node_equal(const_node_pointer a, const_node_pointer b) const {
		return a == b && a != NULL;
	}


	node_pointer _M_find_max(node_pointer node) {
		if (!node) {
			return NULL;
		}
		while (node->right) {
			node = node->right;
		}
		return node;
	}

	node_pointer _M_find_min(node_pointer node) {
		if (!node) {
			return NULL;
		}
		while (node->left) {
			node = node->left;
		}
		return node;
	}

public:

	node_pointer left;
	node_pointer right;
	node_pointer parent;
	color_type color;
	value_type value;

};

}

#endif /* NODE_RED_BLACK_HPP */
