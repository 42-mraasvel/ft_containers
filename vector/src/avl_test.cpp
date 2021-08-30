#include "avl_tree.hpp"
#include "bst.hpp"
#include <iostream>
#include <map>
#include <utility>

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

int TestAVL()
{
	ft::AvlTree<int> tree;

	std::cout << std::boolalpha;

	std::map<int, int> m;



	for (int i = 1000; i >= 0; --i)
	{
		tree.insert(i);
		// m.insert(std::make_pair(i, i));
	}

	tree.print();
	return 0;
}
