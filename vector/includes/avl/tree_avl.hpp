#ifndef TREE_AVL_HPP
# define TREE_AVL_HPP

# include "avl/node_avl.hpp"

# include <cstddef>

template <typename T, typename Alloc>
class TreeAVL {
public:
/* Member Types */
	typedef size_t	size_type;
	typedef Alloc	allocator_type;
	typedef Alloc	allocator_node;

public:
/* Constructors / Destructor */
	TreeAVL() {}
	TreeAVL(const TreeAVL& from) {}

	~TreeAVL() {}

/* Operators */
	TreeAVL& operator=(const TreeAVL& rhs) {}

private:

};

#endif /* TREE_AVL_HPP */
