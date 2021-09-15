// #include "red_black/tree_red_black.hpp"

// #ifdef CATCH_TEST_ENABLED
// #ifndef STD_VECTOR_TESTS
// # include "catch.hpp"

// namespace Test {

// template <typename Node>
// bool isBlack(const Node* root) {
// 	return root == NULL || root->color == Node::BLACK;
// }

// template <typename Node>
// int blackHeight(const Node* root) {
// 	if (root == NULL || (root->left && root->left->right == root)) {
// 		return 0;
// 	}

// 	int blackHeightLeft = blackHeight(root->left);
// 	int blackHeightRight = blackHeight(root->right);
// 	assert(blackHeightLeft == blackHeightRight);

// 	if (isBlack(root)) {
// 		return blackHeightLeft + 1;
// 	}

// 	return blackHeightLeft;
// }

// template <typename Node>
// int testNode(const Node* x) {
// 	if (x == NULL || (x->left && x->left->right == x)) {
// 		return 0;
// 	}

// 	if (x->color == Node::RED) {
// 		assert(x->parent->color == Node::BLACK);
// 	}

// 	assert(testNode(x->left) == testNode(x->right));
// 	return blackHeight(x);
// }

// template <typename Node>
// bool testRedBlackInvariant(const Node* root) {
// 	if (root == NULL) {
// 		return true;
// 	}

// 	assert(root->color == Node::BLACK);
// 	testNode(root);
// 	return true;
// }

// template <typename T>
// bool validRB(const ft::TreeRB<T>& m) {
// 	return testRedBlackInvariant(m.base());
// }

// }

// /* Node Insertion */

// TEST_CASE("Red-Black Insertion case 1", "[red-black]") {
// 	ft::TreeRB<int> t;

// 	for (int i = 0; i < 10; ++i) {
// 		t.insert(i);
// 	}

// 	REQUIRE(Test::validRB(t) == true);
// }

// /* Node Deletion */

// TEST_CASE("Red-Black erase case 0", "[red-black]") {
// 	ft::TreeRB<int> m;

// 	for (int i = 0; i < 6; ++i) {
// 		m.insert(i);
// 	}

// 	m.erase(4);

// 	REQUIRE(Test::validRB(m) == true);
// }

// TEST_CASE("Red-Black erase case 1", "[red-black]") {
// 	ft::TreeRB<int> m;

// 	for (int i = 0; i < 10; ++i) {
// 		m.insert(i);
// 	}

// 	m.erase(4);

// 	REQUIRE(Test::validRB(m) == true);
// }

// TEST_CASE("Red-Black erase case 2", "[red-black]") {
// 	ft::TreeRB<int> m;

// 	for (int i = 0; i < 8; ++i) {
// 		m.insert(i);
// 	}

// 	m.erase(1);

// 	REQUIRE(Test::validRB(m) == true);
// }

// TEST_CASE("Red-Black erase case 3", "[red-black]") {
// 	ft::TreeRB<int> m;

// 	for (int i = 0; i < 16; ++i) {
// 		m.insert(i);
// 	}

// 	m.erase(2);
// 	m.erase(1);
// 	m.erase(5);
// 	m.insert(5);
// 	m.erase(6);

// 	m.erase(0);

// 	REQUIRE(Test::validRB(m) == true);
// }

// TEST_CASE("Red-Black erase case 4", "[red-black]") {
// 	ft::TreeRB<int> m;

// 	for (int i = 0; i < 6; ++i) {
// 		m.insert(i);
// 	}

// 	m.erase(3);

// 	REQUIRE(Test::validRB(m) == true);
// }

// TEST_CASE("Red-Black hint test", "[red-black]") {
// 	ft::TreeRB<int> s;
// 	s.insert(42);
// 	s.insert(69);

// 	auto it = s.begin();
// 	++it;
// 	REQUIRE(*it == 69);
// 	s.insert(it, 420);

// 	REQUIRE(s.size() == 3);

// 	REQUIRE(Test::validRB(s) == true);
// }

// #endif /* STD_VECTOR_TESTS */
// #endif /* CATCH_TEST_ENABLED */
