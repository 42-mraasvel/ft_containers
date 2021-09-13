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

public:

	NodeRB()
	: left(NULL), right(NULL), parent(NULL), color(RED) {}

	NodeRB(const T& val)
	: left(NULL), right(NULL), parent(NULL), color(RED), value(val) {}

	NodeRB(const T& val, NodeRB* parent)
	: left(NULL), right(NULL), parent(parent), color(RED), value(val) {}

	~NodeRB() {}

	const T& getValue() const {
		return value;
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
