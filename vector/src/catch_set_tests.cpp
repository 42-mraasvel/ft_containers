#include "set.hpp"
#include "settings.hpp"

#include <functional>
#include <cstdlib>
#include <ctime>

#ifdef CATCH_TEST_ENABLED
# include "catch.hpp"

/* Constructors */

TEST_CASE("set default constructor", "[set]") {

	NS::set<int> s;

	REQUIRE(s.empty() == true);
	REQUIRE(s.size() == 0);
}

TEST_CASE("set range constructor", "[set]") {
	const int table[] = {0, 1, 2, 3, 4};
	const int size = sizeof(table) / sizeof(int);

	const NS::set<int> s(table, table + size);

	NS::set<int>::const_iterator it = s.begin();
	NS::set<int>::const_iterator ite = s.end();

	REQUIRE(s.size() == size);

	int i = 0;
	while (it != ite) {
		REQUIRE(i == *it);
		++it;
		++i;
	}
}

TEST_CASE("set range constructor 2", "[set]") {
	std::vector<int> v;
	srand(time(0));
	for (int i = 0; i < 100; ++i) {
		v.push_back(rand());
	}


	NS::set<int> s(v.begin(), v.end());
	std::sort(v.begin(), v.end());

	auto it2 = v.begin();
	for (auto it = s.begin(); it != s.end(); ++it, ++it2) {
		REQUIRE(*it == *it2);
	}
}

TEST_CASE("set copy constructor", "[set]") {
	NS::set<int> s;

	for (int i = 0; i < 100; ++i) {
		s.insert(rand());
	}

	NS::set<int> s2(s);

	// REQUIRE(s == s2);
}

/* Assignment */

TEST_CASE("set copy assignment", "[set]") {
	NS::set<int> s;

	for (int i = 0; i < 100; ++i) {
		s.insert(rand());
	}

	NS::set<int> s2;
	s2 = s;
	// REQUIRE(s == s2);
	s.clear();
	s2 = s;
	// REQUIRE(s == s2);
}

/* Iterators */

TEST_CASE("set iterators", "[set]") {
	NS::set<int> s;

	REQUIRE(s.begin() == s.end());
	for (int i = -100; i < 100; ++i) {
		s.insert(i);
	}

	REQUIRE(s.size() == 200);

	auto it = s.begin();
	for (int i = -100; i < 100; ++i) {
		REQUIRE(i == *it);
		++it;
	}
}

TEST_CASE("set const iterators", "[set]") {
	std::vector<int> v;

	for (int i = -100; i < 100; ++i) {
		v.push_back(i);
	}

	const NS::set<int> s(v.begin(), v.end());

	NS::set<int>::const_iterator it = s.begin();
	REQUIRE(s.size() == 200);

	for (int i = -100; i < 100; ++i) {
		REQUIRE(i == *it);
		++it;
	}
}

TEST_CASE("set iterator to const iterator conversion", "[set]") {
	NS::set<int> s;

	s.insert(42);
	NS::set<int>::iterator it = s.begin();
	NS::set<int>::iterator ite = s.end();
	NS::set<int>::const_iterator const_it = it;
	NS::set<int>::const_iterator const_ite = ite;

	REQUIRE(it == const_it);
	REQUIRE(const_it == it);
	REQUIRE(ite == const_ite);
	REQUIRE(const_ite == ite);
}

TEST_CASE("set iterator other", "[set]") {
	NS::set<int> s;
	NS::set<int> s2;

	REQUIRE(s.begin() != s2.begin());
	REQUIRE(s.begin() == s.end());
	REQUIRE(s.end() != s2.end());
}

TEST_CASE("set reverse iterator", "[set]") {
	NS::set<int> s;

	REQUIRE(s.rbegin() == s.rend());

	for (int i = -100; i < 100; ++i) {
		s.insert(i + 1);
	}

	auto rit = s.rbegin();

	REQUIRE(s.size() == 200);

	for (int i = 100; i > -100; --i) {
		REQUIRE(i == *rit);
		++rit;
	}
}

TEST_CASE("set reverse iterator to const iterator conversion", "[set]") {
	NS::set<int> s;

	s.insert(42);
	NS::set<int>::reverse_iterator it = s.rbegin();
	NS::set<int>::reverse_iterator ite = s.rend();
	NS::set<int>::const_reverse_iterator const_it = it;
	NS::set<int>::const_reverse_iterator const_ite = ite;

	REQUIRE(it == const_it);
	REQUIRE(const_it == it);
	REQUIRE(ite == const_ite);
	REQUIRE(const_ite == ite);

}

TEST_CASE("set reverse iterator other", "[set]") {
	NS::set<int> s;
	NS::set<int> s2;

	REQUIRE(s.rbegin() != s2.rbegin());
	REQUIRE(s.rbegin() == s.rend());
	REQUIRE(s.rend() != s2.rend());
}

TEST_CASE("set iterator end testing", "[set]") {
	NS::set<int> s;

	s.insert(42);

	auto it = s.end();
	--it;
	REQUIRE(*it == 42);

	auto rit = s.rend();
	--rit;
	REQUIRE(*rit == 42);
	++rit;
	REQUIRE(rit == s.rend());
}

/* Capacity */

TEST_CASE("set size", "[set]") {
	NS::set<int> s;

	REQUIRE(s.size() == 0);
	s.insert(42);
	REQUIRE(s.size() == 1);
	for (int i = 0; i < 100; ++i) {
		s.insert(i);
	}

	REQUIRE(s.size() == 100);
	s.clear();
	REQUIRE(s.size() == 0);
	s.clear();
}

/* Modifiers */

TEST_CASE("set insert single element", "[set]") {
	NS::set<int> s;

	const int MAX_SIZE = 100000;

	s.insert(42);

	REQUIRE(*s.begin() == 42);
	REQUIRE(s.size() == 1);

	for (int i = 0; i < MAX_SIZE; ++i) {
		s.insert(i);
	}
	REQUIRE(s.size() == MAX_SIZE);
}

TEST_CASE("set insert hint", "[set]") {
	NS::set<int> s;

	s.insert(42);
	s.insert(69);

	auto it = s.begin();
	++it;
	REQUIRE(*it == 69);
	s.insert(it, 420);

	REQUIRE(s.size() == 3);
}

TEST_CASE("set insert range", "[set]") {
	std::vector<int> v;

	for (int i = 0; i < 50; ++i) {
		v.push_back(rand());
	}

	NS::set<int> s;

	s.insert(v.begin(), v.end());

	std::sort(v.begin(), v.end());

	auto it2 = v.begin();
	for (auto it = s.begin(); it != s.end(); ++it, ++it2) {
		REQUIRE(*it == *it2);
	}
}

TEST_CASE("set erase position", "[set]") {
	NS::set<int> s;

	s.insert(42);
	s.erase(s.begin());
	REQUIRE(s.size() == 0);

	for (int i = 0; i < 50; ++i) {
		s.insert(i);
	}

	auto it = s.begin();
	for (int i = 0; i < 25; ++i) {
		++it;
	}

	s.erase(it++);
	s.erase(it, s.end());
	REQUIRE(s.size() == 25);
}

TEST_CASE("set erase value", "[set]") {
	NS::set<int> s;

	for (int i = 0; i < 10; ++i) {
		s.insert(i);
	}

	s.erase(10);
	REQUIRE(s.size() == 10);
	s.erase(9);
	REQUIRE(s.size() == 9);
	REQUIRE(*s.rbegin() == 8);
}

TEST_CASE("set erase range", "[set]") {
	NS::set<int> s;

	for (int i = 0; i < 10; ++i) {
		s.insert(i);
	}

	s.erase(s.begin(), s.end());
	REQUIRE(s.size() == 0);

	for (int i = 0; i < 100; ++i) {
		s.insert(i);
	}

	auto it = s.begin();
	auto ite = s.begin();
	for (int i = 0; i < 50; ++i) {
		++it;
		++ite;
	}

	for (int i = 0; i < 25; ++i) {
		++ite;
	}

	s.erase(it, ite);
	REQUIRE(s.size() == 75);
}

TEST_CASE("set swap", "[set]") {
	NS::set<int> s;
	NS::set<int> s2;

	s.insert(42);
	s2.insert(420);

	REQUIRE(*s.begin() == 42);
	REQUIRE(*s2.begin() == 420);

	NS::set<int>::iterator it = s.begin();
	NS::set<int>::iterator ite = s.end();

	s.swap(s2);
	REQUIRE(*s.begin() == 420);
	REQUIRE(*s2.begin() == 42);
	REQUIRE(it == s2.begin());
}

/* Observers */

/* Operations */

#endif /* CATCH_TEST_ENABLED */

