#ifndef NODE_AVL_HPP
# define NODE_AVL_HPP

# include "node_bst.hpp"

namespace ft {

template <typename T>
class NodeAVL : public NodeBst<T> {
/* Member Types */
private:
	typedef NodeBst<T> parent;

/* Constructors / Destructors */
public:
	NodeAVL() {}

	NodeAVL(const NodeAVL& from)
	: _height(from.get_height()), parent(from) {}

	~NodeAVL() {}

/* Operators */
	NodeAVL& operator=(const NodeAVL& rhs) {
		if (this == &rhs)
			return *this;
		_height = rhs.height;
		parent::operator=(rhs);
		return *this;
	}

/* Setters / Getters */
	void update_height() {
		_height = ft::max(_M_calculate_height(this->left()), _M_calculate_height(this->right())) + 1;
	}

	int get_height() const {
		return _height;
	}

	int get_balance() const {
		return _M_calculate_height(this->left()) - _M_calculate_height(this->right());
	}

/* Private Member Functions */
private:
	static int _M_calculate_height(const NodeAVL* node) {
		if (node == NULL)
			return -1;
		return node->get_height();
	}

/* Member Variables */
private:
	int _height;

};

}

#endif /* NODE_AVL_HPP */
