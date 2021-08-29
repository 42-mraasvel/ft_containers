#include "avl_tree.hpp"
#include "bst.hpp"
#include <iostream>

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

*/

int TestAVL()
{
	ft::AvlTree<int> tree;

	std::cout << std::boolalpha;

	tree.insert(41);
	tree.insert(20);
	tree.insert(65);
	tree.insert(50);
	tree.insert(11);
	tree.insert(29);
	tree.insert(26);
	tree.insert(23);

	tree.print();

	std::cout << ft::BSTree<int>::RED << std::endl;

	return 0;
}
