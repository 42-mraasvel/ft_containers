#ifndef NODE_RED_BLACK_HPP
# define NODE_RED_BLACK_HPP

namespace ft {

template <typename T>
class NodeRB {

public:

static const bool RED = true;
static const bool BLACK = false;

private:

	NodeRB* left;
	NodeRB* right;
	NodeRB* parent;
	bool color;
	T value;

};

}


#endif /* NODE_RED_BLACK_HPP */
