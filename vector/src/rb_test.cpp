#include "red_black/tree_red_black.hpp"
#include "red_black/node_red_black.hpp"
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <cstddef>

/*
RBT INVARIANT

	1. Every node has a colour either red or black.
	2. The root and the leaves (NIL's) of the tree are always black.
	3. There are no two adjacent red nodes (A red node cannot have a red parent or red child).
	4. Every path from a node (including root) to any of its descendants NULL nodes has the same number of black nodes.
*/
using ft::NodeRB;
using ft::TreeRB;

template <typename Node>
bool isBlack(const Node* root) {
	return root == NULL || root->color == Node::BLACK;
}

template <typename Node>
int blackHeight(const Node* root) {
	if (root == NULL) {
		return 0;
	}

	int blackHeightLeft = blackHeight(root->left);
	int blackHeightRight = blackHeight(root->right);
	assert(blackHeightLeft == blackHeightRight);

	if (isBlack(root)) {
		return blackHeightLeft + 1;
	}

	return blackHeightLeft;
}

template <typename T>
int testNode(const NodeRB<T>* x) {
	if (x == NULL) {
		return 0;
	}

	if (x->color == NodeRB<T>::RED) {
		assert(x->parent->color == NodeRB<T>::BLACK);
	}

	assert(testNode(x->left) == testNode(x->right));
	return blackHeight(x);
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


template <typename Node>
void printNode(const Node* x) {
	std::cout << "VAL(" << x->value << "), COLOR(";
	if (x->color == Node::BLACK) {
		std::cout << "BLACK";
	} else {
		std::cout << "RED";
	}
	std::cout << "), HEIGHT(" << blackHeight(x) << ")" << std::endl;
}

template <typename Node>
void printTree(const Node* root) {
	if (root == NULL) {
		return;
	}

	printNode(root);
	printTree(root->left);
	printTree(root->right);
}

void testRedBlack() {
	std::cout << std::boolalpha;

	TreeRB<int> m;

	for (int i = 0; i < 10; ++i) {
		m.insert(i);
	}

	for (int i = 9; i >= 0; --i) {
		m.erase(i);
	}

	std::cout << "SIZE(" << m.size() << ')' << std::endl;

	TreeRB<int>::node_pointer root = m.base();
	printTree(root);
	std::cout << testRedBlackInvariant(root) << std::endl;
	
	m.clear();

}
