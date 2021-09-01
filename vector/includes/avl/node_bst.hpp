#ifndef NODE_BST_HPP
# define NODE_BST_HPP

namespace ft {

template <typename T>
class NodeBst {
public:
	typedef T key_type;

public:
/* Constructors */
	NodeBst()
	: _parent(NULL), _left(NULL), _right(NULL) {}

	NodeBst(const T& key)
	: _key(key), _parent(NULL), _left(NULL), _right(NULL) {}

	NodeBst(const NodeBst& node)
	: _key(node.key()), _parent(node.parent()), _left(node.left()), _right(node.right()) {}

	virtual ~NodeBst() {}

/* Operators */
	NodeBst& operator=(const NodeBst& rhs) {
		if (this == &rhs)
			return *this;
		key() = rhs.parent();
		parent() = rhs.parent();
		left() = rhs.left();
		right() = rhs.right();
		return *this;
	}

/* Public Member Functions */
	NodeBst* next() {
		if (right())
			return _M_find_min(right());

		NodeBst* current = parent();
		NodeBst* prev = this;
		while (current) {
			if (prev == current->left)
				return current;
			prev = current;
			current = current->parent();
		}
		return NULL;
	}

	NodeBst* prev() {
		if (left())
			return _M_find_max(left());

		NodeBst* current = parent();
		NodeBst* prev = this;
		while (current) {
			if (prev == current->right)
				return current;
			prev = current;
			current = current->parent;
		}
		return NULL;
	}

/* Getters */
	key_type& key() {
		return _key;
	}

	const key_type& key() const {
		return _key;
	}

	NodeBst*& parent() {
		return _parent;
	}

	const NodeBst*& parent() const {
		return _parent;
	}

	NodeBst*& left() {
		return _left;
	}

	const NodeBst*& left() const {
		return _left;
	}

	NodeBst*& right() {
		return _right;
	}

	const NodeBst*& right() const {
		return _right;
	}

private:
/* Private Utility Member Functions */
	NodeBst* _M_find_max(NodeBst* node) {
		if (!node)
			return NULL;
		while (node->right)
			node = node->right;
		return node;
	}

	NodeBst* _M_find_min(NodeBst* node) {
		if (!node)
			return NULL;
		while (node->left)
			node = node->left;
		return node;
	}

/* Member Variables */
protected:
	key_type _key;
	NodeBst* _parent;
	NodeBst* _left;
	NodeBst* _right;

};

}


#endif /* NODE_BST_HPP */
