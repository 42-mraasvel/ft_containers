#include "avl_tree.hpp"
#include "bst.hpp"
#include "node_avl.hpp"
#include "tree_avl.hpp"
#include "map.hpp"
#include "pair.hpp"
#include "make_pair.hpp"
#include "iterator_avl.hpp"
#include "iterator_traits.hpp"
#include <iostream>
#include <map>
#include <utility>
#include <cassert>
#include <vector>


template <typename T>
int calculateHeight(ft::NodeAVL<T>* node)
{
	if (node == NULL)
		return -1;
	
	return ft::max(calculateHeight(node->left), calculateHeight(node->right)) + 1;
}

template <typename T>
int calculateBalance(ft::NodeAVL<T>* node)
{
	return calculateHeight(node->left) - calculateHeight(node->right);
}

template <typename T>
bool validNode(ft::NodeAVL<T>* node)
{
	int balance = calculateBalance(node);

	assert(node->get_height() == calculateHeight(node));
	assert(node->get_balance() == balance);
	assert(ft::abs(calculateBalance(node)) <= 1);

	if (node->left)
	{
		assert(node->left->parent == node);
		assert(node->left->key.first < node->key.first);
	}
	
	if (node->right)
	{
		assert(node->right->parent == node);
		assert(node->right->key.first > node->key.first);
	}

	return true;
}

template <typename T>
bool validAvl(ft::NodeAVL<T>* root)
{
	if (root == NULL)
		return true;

	if (!validAvl(root->left))
		return false;
	if (!validNode(root))
		return false;
	if (!validAvl(root->right))
		return false;
	return true;
}

template <typename T>
void printNode(ft::NodeAVL<T>* node) {
	std::cout << "VAL(" << node->key.first << "), HEIGHT("
	<< node->get_height() << "), BALANCE(" << node->get_balance() << ")"
	<< std::endl;
}

template <typename T>
void printTree(ft::NodeAVL<T>* root) {
	if (root == NULL)
		return;

	printNode(root);
	printTree(root->left);
	printTree(root->right);
}

/*
Rotation Tests:


	Simple Left-Heavy:
		Right
		Left-Right Rotation
	Insertions:
		41
		20
		65
		50
		11
		29
		26
		23 | 27 (straight vs zig-zag)

	Simple Right-Heavy:
		Left
		Right-Left Rotation
	Insertions:


	Complex Rotation!
	Insertions:
		50
		60
		30
		20
		40
		45

	Insertions:
		0
		1
		...
		n 

*/

typedef ft::NodeAVL < ft::pair<const int, int> > node_type;

int TestAVL()
{
	std::cout << std::boolalpha;
	ft::map<int, int> m;

	for (int i = 0; i < 10; ++i) {
		m.insert(ft::make_pair(i, i));
	}

	ft::map<int, int>::iterator it = m.begin();
	ft::map<int, int>::iterator ite = m.end();

	for (int i = 0; i < 9; ++i) {
		std::cout << it->first << std::endl;
		++it;
	}
	++it;
	std::cout << it.is_end() << std::endl;
	// std::cout << it.ptr() << std::endl;
	// std::cout << (void*)m.max() << std::endl;
	// std::cout << it->first << std::endl;

	// std::cout << "MAX: " << m.max()->key.first << std::endl;
	// std::cout << "MIN: " << m.min()->key.first << std::endl;


	/* CONFIRM AVL */
	node_type* ptr = m.root();
	printTree(ptr);
	std::cout << "SIZE(" << m.size() << ")" << std::endl;
	validAvl(ptr);


	return 0;
}
