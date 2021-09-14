#ifndef NODE_RED_BLACK_HPP
# define NODE_RED_BLACK_HPP

# include <cstddef>
# include <iostream> // REMOVE

namespace ft {

template <typename T>
class NodeRB {

public:

	typedef bool color_type;

	static const color_type RED = true;
	static const color_type BLACK = false;

public:

	NodeRB()
	: left(NULL), right(NULL), parent(NULL), color(RED) {}

	NodeRB(const T& val)
	: left(NULL), right(NULL), parent(NULL), color(RED), value(val) {}

	NodeRB(const T& val, NodeRB* parent)
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

	const T& getValue() const {
		return value;
	}

/* Iterating */
	NodeRB* next() {
		if (right) {
			return _M_find_min(right);
		} else if (parent && parent->left == static_cast<void*>(this)) {
			return parent;
		}
		return _M_next_node(parent);
	}

	const NodeRB* next() const {
		if (right) {
			return _M_find_min(right);
		} else if (parent && parent->left == static_cast<void*>(this)) {
			return parent;
		}
		return _M_next_node(parent);
	}

	NodeRB* prev() {
		if (left) {
			return _M_find_max(left);
		} else if (parent && parent->right == static_cast<void*>(this)) {
			return parent;
		}
		return _M_prev_node(parent);
	}

	const NodeRB* prev() const {
		if (left) {
			return _M_find_max(left);
		} else if (parent && parent->right == static_cast<void *>(this)) {
			return parent;
		}
		return _M_prev_node(parent);
	}

private:
	NodeRB* _M_next_node(NodeRB* node) {
		const NodeRB* prev = NULL;
		while (node) {
			if (_M_node_equal(node->left, prev)) {
				return node;
			}
			prev = node;
			node = node->parent;
		}
		return NULL;
	}

	NodeRB* _M_prev_node(NodeRB* node) {
		const NodeRB* prev = NULL;
		while (node) {
			if (_M_node_equal(node->right, prev)) {
				return node;
			}
			prev = node;
			node = node->parent;
		}
		return NULL;
	}

	bool _M_node_equal(const NodeRB* a, const NodeRB* b) const {
		return a == b && a != NULL;
	}


	NodeRB* _M_find_max(NodeRB* node) {
		if (!node) {
			return NULL;
		}
		while (node->right) {
			node = node->right;
		}
		return node;
	}

	NodeRB* _M_find_min(NodeRB* node) {
		if (!node) {
			return NULL;
		}
		while (node->left) {
			node = node->left;
		}
		return node;
	}

public:

	NodeRB* left;
	NodeRB* right;
	NodeRB* parent;
	color_type color;
	T value;

};

}

#endif /* NODE_RED_BLACK_HPP */
