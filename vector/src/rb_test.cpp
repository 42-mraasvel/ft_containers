#include <cstdlib>
#include <cassert>
#include "red_black/node_red_black.hpp"

/*
RBT INVARIANT

	1. Every node has a colour either red or black.
	2. The root and the leaves (NIL's) of the tree are always black.
	3. There are no two adjacent red nodes (A red node cannot have a red parent or red child).
	4. Every path from a node (including root) to any of its descendants NULL nodes has the same number of black nodes.
*/

using ft::NodeRB;

template <typename T>
int testNode(const NodeRB<T>* x) {
	if (x == NULL) {
		return 0;
	}

	int count = 0;

	if (x->color == NodeRB<T>::RED) {
		assert(x->parent->color == NodeRB<T>::BLACK);
	} else {
		count += 1;
	}

	int count_left = testNode(x->left);
	int count_right = testNode(x->right);

	assert(count_left == count_right);
	return count + count_left + count_right;
}

template <typename T>
bool testRedBlackInvariant(const NodeRB<T>* root) {
	if (root == NULL) {
		return true;
	}

	assert(root->color == NodeRB<T>::BLACK);
	testNode(root);
	return true;
}

void testRedBlack() {
}
