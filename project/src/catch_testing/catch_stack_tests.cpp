#include "settings.hpp"
#include "catch.hpp"

#include "containers/stack.hpp"
#include <stack>

/*
Tests:
	Constructor
	top
	push
	pop
*/

TEST_CASE("stack default constructor", "[stack]") {

	ft::vector<int> v;

	for (int i = 0; i < 100; ++i) {
		v.push_back(i);
	}

	NS::stack<int, ft::vector<int> > s(v);
	REQUIRE(s.size() == 100);

	NS::stack<int> s2;
	REQUIRE(s2.size() == 0);
}

TEST_CASE("stack push/top", "[stack]") {
	NS::stack<int> s;

	s.push(42);
	REQUIRE(s.top() == 42);
	REQUIRE(s.size() == 1);

	for (int i = 0; i < 100; ++i) {
		s.push(i);
	}

	REQUIRE(s.top() == 99);
	REQUIRE(s.size() == 101);
}

TEST_CASE("stack pop", "[stack]") {
	NS::stack<int> s;

	for (int i = 0; i < 500; ++i) {
		s.push(i);
	}

	REQUIRE(s.top() == 499);
	s.pop();
	REQUIRE(s.top() == 498);
	REQUIRE(s.size() == 499);
}
