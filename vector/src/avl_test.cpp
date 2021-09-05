#include "avl_tree.hpp"
#include "bst.hpp"
#include "node_avl.hpp"
#include "tree_avl.hpp"
#include "map.hpp"
#include <iostream>
#include <map>
#include <utility>
#include <cassert>


// template <typename NodeType>
// int calculateHeight(NodeType* node)
// {
// 	if (node == NULL)
// 		return -1;
	
// 	return ft::max(calculateHeight(node->left()), calculateHeight(node->right())) + 1;
// }

// template <typename NodeType>
// int calculateBalance(NodeType* node)
// {
// 	return calculateHeight<node_type>(node->left()) - calculateHeight(node->right());
// }

// template <typename NodeType>
// bool validNode(NodeType* node)
// {
// 	int balance = calculateBalance<node_type>(node);
	
// 	assert(node->get_height() == calculateHeight<node_type>(node));
	// assert(node->get_balance() == balance);
	// assert(ft::abs(calculateBalance(node)) <= 1);

	// if (node->left)
	// {
	// 	assert(node->left()->parent() == node);
	// 	assert(node->left()->key().first < node->key().second);
	// }
	
	// if (node->right)
	// {
	// 	assert(node->right()->parent() == node);
	// 	assert(node->right()->key().first > node->key().second);
	// }

// 	return true;
// }

template <typename NodeType>
bool validAvl(NodeType* root)
{
	if (root == NULL)
		return true;

	if (!validAvl(root->left()))
		return false;
	// if (!validNode<node_type>(root))
	// 	return false;
	// if (!validAvl<node_type>(root->right()))
	// 	return false;
	return true;
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
	ft::map<int, int> m;

	node_type* ptr = m.root();
	validAvl<node_type>(ptr);

	return 0;
}
