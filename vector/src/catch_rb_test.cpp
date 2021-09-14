#include "red_black/tree_red_black.hpp"

#ifdef CATCH_TEST_ENABLED
#ifndef STD_VECTOR_TESTS
# include "catch.hpp"

template <typename Node>
bool _TEST_isBlack(const Node* root) {
	return root == NULL || root->color == Node::BLACK;
}

template <typename Node>
int _TEST_blackHeight(const Node* root) {
	if (root == NULL) {
		return 0;
	}

	int blackHeightLeft = _TEST_blackHeight(root->left);
	int blackHeightRight = _TEST_blackHeight(root->right);
	assert(blackHeightLeft == blackHeightRight);

	if (_TEST_isBlack(root)) {
		return blackHeightLeft + 1;
	}

	return blackHeightLeft;
}

template <typename Node>
int _TEST_testNode(const Node* x) {
	if (x == NULL) {
		return 0;
	}

	if (x->color == Node::RED) {
		assert(x->parent->color == Node::BLACK);
	}

	assert(_TEST_testNode(x->left) == _TEST_testNode(x->right));
	return _TEST_blackHeight(x);
}

template <typename Node>
bool _TEST_testRedBlackInvariant(const Node* root) {
	if (root == NULL) {
		return true;
	}

	assert(root->color == Node::BLACK);
	_TEST_testNode(root);
	return true;
}

template <typename T>
bool _TEST_validRB(const ft::TreeRB<T>& m) {
	return _TEST_testRedBlackInvariant(m.base());
}

/* Node Insertion */

TEST_CASE("Red-Black Insertion case 1", "[red-black]") {
	ft::TreeRB<int> t;

	for (int i = 0; i < 10; ++i) {
		t.insert(i);
	}

	REQUIRE(_TEST_validRB(t) == true);
}

/* Node Deletion */

TEST_CASE("Red-Black erase case 0", "[red-black]") {
	ft::TreeRB<int> m;

	for (int i = 0; i < 6; ++i) {
		m.insert(i);
	}

	m.erase(4);

	REQUIRE(_TEST_validRB(m) == true);
}

TEST_CASE("Red-Black erase case 1", "[red-black]") {
	ft::TreeRB<int> m;

	for (int i = 0; i < 10; ++i) {
		m.insert(i);
	}

	m.erase(4);

	REQUIRE(_TEST_validRB(m) == true);
}

TEST_CASE("Red-Black erase case 2", "[red-black]") {
	ft::TreeRB<int> m;

	for (int i = 0; i < 8; ++i) {
		m.insert(i);
	}

	m.erase(1);

	REQUIRE(_TEST_validRB(m) == true);
}

TEST_CASE("Red-Black erase case 3", "[red-black]") {
	ft::TreeRB<int> m;

	for (int i = 0; i < 16; ++i) {
		m.insert(i);
	}

	m.erase(2);
	m.erase(1);
	m.erase(5);
	m.insert(5);
	m.erase(6);

	m.erase(0);

	REQUIRE(_TEST_validRB(m) == true);
}

TEST_CASE("Red-Black erase case 4", "[red-black]") {
	ft::TreeRB<int> m;

	for (int i = 0; i < 6; ++i) {
		m.insert(i);
	}

	m.erase(3);

	REQUIRE(_TEST_validRB(m) == true);
}

TEST_CASE("Red-Black hint test", "[red-black]") {
	ft::TreeRB<int> s;
	s.insert(42);
	s.insert(69);

	auto it = s.begin();
	++it;
	REQUIRE(*it == 69);
	s.insert(it, 420);

	REQUIRE(s.size() == 3);

	REQUIRE(_TEST_validRB(s) == true);
}

#endif /* STD_VECTOR_TESTS */
#endif /* CATCH_TEST_ENABLED */
