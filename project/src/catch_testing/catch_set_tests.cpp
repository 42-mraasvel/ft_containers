#include "containers/set.hpp"
#include "settings.hpp"

#include <functional>
#include <cstdlib>
#include <ctime>

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

	REQUIRE(s == s2);
}

/* Assignment */

TEST_CASE("set copy assignment", "[set]") {
	NS::set<int> s;

	for (int i = 0; i < 100; ++i) {
		s.insert(rand());
	}

	NS::set<int> s2;
	s2 = s;
	REQUIRE(s == s2);
	s.clear();
	s2 = s;
	REQUIRE(s == s2);
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

TEST_CASE("Red-Black erase case 0", "[red-black]") {
	NS::set<int> m;

	for (int i = 0; i < 6; ++i) {
		m.insert(i);
	}

	m.erase(4);

	for (int i = 0; i < 10000; ++i) {
		m.insert(i);
	}

	m.erase(m.begin(), m.end());

	m.insert(42);

	REQUIRE(m.size() == 1);
}

TEST_CASE("Red-Black erase case 1", "[red-black]") {
	NS::set<int> m;

	for (int i = 0; i < 10; ++i) {
		m.insert(i);
	}

	m.erase(4);

	for (int i = 0; i < 10000; ++i) {
		m.insert(i);
	}

	m.erase(m.begin(), m.end());

	m.insert(42);

	REQUIRE(m.size() == 1);
}

TEST_CASE("Red-Black erase case 2", "[red-black]") {
	NS::set<int> m;

	for (int i = 0; i < 8; ++i) {
		m.insert(i);
	}

	m.erase(1);

	for (int i = 0; i < 10000; ++i) {
		m.insert(i);
	}

	m.erase(m.begin(), m.end());

	m.insert(42);

	REQUIRE(m.size() == 1);
}

TEST_CASE("Red-Black erase case 3", "[red-black]") {
	NS::set<int> m;

	for (int i = 0; i < 16; ++i) {
		m.insert(i);
	}

	m.erase(2);
	m.erase(1);
	m.erase(5);
	m.insert(5);
	m.erase(6);

	m.erase(0);

	for (int i = 0; i < 10000; ++i) {
		m.insert(i);
	}

	m.erase(m.begin(), m.end());

	m.insert(42);

	REQUIRE(m.size() == 1);
}

TEST_CASE("Red-Black erase case 4", "[red-black]") {
	NS::set<int> m;

	for (int i = 0; i < 6; ++i) {
		m.insert(i);
	}

	m.erase(3);

	for (int i = 0; i < 10000; ++i) {
		m.insert(i);
	}

	m.erase(m.begin(), m.end());
	m.insert(42);

	REQUIRE(m.size() == 1);
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
	(void)ite;

	s.swap(s2);
	REQUIRE(*s.begin() == 420);
	REQUIRE(*s2.begin() == 42);
	REQUIRE(it == s2.begin());

	++it;
	REQUIRE(it == s2.end());
	it--;
	REQUIRE(it == s2.begin());
}

TEST_CASE("set clear", "[set]") {
	NS::set<int> s;

	s.clear();
	s.clear();

	for (int i = 0; i < 100; ++i) {
		s.insert(i);
	}

	REQUIRE(s.size() == 100);

	int i = 0;
	for (NS::set<int>::iterator it = s.begin(); it != s.end(); it++, i++) {
		REQUIRE(i == *it);
	}
	REQUIRE(i == 100);

	NS::set<int>::iterator ite = s.end();

	s.clear();
	REQUIRE(s.begin() == s.end());

	s.insert(42);
	--ite;
	REQUIRE(*ite == 42);
}

/* Operations */

TEST_CASE("set find", "[set]") {
	NS::set<int> s;

	for (int i = 0; i < 100; ++i) {
		s.insert(i);
	}

	NS::set<int>::iterator it = s.find(42);
	NS::set<int>::const_iterator cit = s.find(42);

	REQUIRE(it != s.end());
	REQUIRE(cit != s.end());
	REQUIRE(*it == 42);
	REQUIRE(*cit == 42);

	it = s.find(420);
	cit = s.find(420);

	REQUIRE(it == s.end());
	REQUIRE(cit == s.end());
}

TEST_CASE("set count", "[set]") {
	NS::set<int> s;

	const int SIZE = 20;
	const int TEST_SIZE = SIZE + 20;

	REQUIRE(s.count(42) == 0);

	for (int i = 0; i < SIZE; ++i) {
		s.insert(i);
	}


	for (int i = 0; i < TEST_SIZE; ++i) {
		if (i < SIZE) {
			REQUIRE(s.count(i) == 1);
		} else {
			REQUIRE(s.count(i) == 0);
		}
	}
}

TEST_CASE("set lower bound", "[set]") {
	NS::set<int> s;

	for (int i = 1; i < 10; ++i) {
		s.insert(i * 10);
	} // 10 20 30 40 50 60 70 80 90

	NS::set<int>::iterator it = s.lower_bound(30);
	REQUIRE(*it == 30);
	it = s.lower_bound(35);
	REQUIRE(*it == 40);
	it = s.lower_bound(95);
	REQUIRE(it == s.end());
	it = s.lower_bound(0);
	REQUIRE(*it == 10);
	REQUIRE(it == s.begin());
}

TEST_CASE("set upper bound", "[set]") {
	NS::set<int> s;

	for (int i = 1; i < 10; ++i) {
		s.insert(i * 10);
	} // 10 20 30 40 50 60 70 80 90

	NS::set<int>::iterator it = s.upper_bound(10);
	REQUIRE(*it == 20);
	it = s.upper_bound(90);
	REQUIRE(it == s.end());
	it = s.upper_bound(10);
	REQUIRE(*it == 20);
	it = s.upper_bound(5);
	REQUIRE(*it == 10);
	REQUIRE(it == s.begin());
}

TEST_CASE("set equal range", "[set]") {
	NS::set<int> s;

	for (int i = 1; i < 10; ++i) {
		s.insert(i * 10);
	}

	NS::pair<NS::set<int>::iterator, NS::set<int>::iterator> p;

	p = s.equal_range(10);

	REQUIRE(*(p.first) == 10);
	REQUIRE(*(p.second) == 20);
	REQUIRE(p.first == s.lower_bound(10));
	REQUIRE(p.second == s.upper_bound(10));

	p = s.equal_range(15);
	REQUIRE(*(p.first) == 20);
	REQUIRE(*(p.first) == *(p.second));
	REQUIRE(p.first == p.second);

	s.erase(p.first);
	p = s.equal_range(10);
	REQUIRE(*(p.first) == 10);
	REQUIRE(*(p.second) == 30);
}

/* Comparisons */

TEST_CASE("set comparison operators", "[set]") {

	std::vector<int> v_alice{1, 2, 3};
	std::vector<int> v_bob{7, 8, 9, 10};
	std::vector<int> v_eve{1, 2, 3};

	NS::set<int> alice(v_alice.begin(), v_alice.end());
	NS::set<int> bob(v_bob.begin(), v_bob.end());
	NS::set<int> eve(v_eve.begin(), v_eve.end());

	REQUIRE(!(alice == bob));
	REQUIRE(alice != bob);
	REQUIRE(alice < bob);
	REQUIRE(alice <= bob);
	REQUIRE(!(alice > bob));
	REQUIRE(!(alice >= bob));

	REQUIRE(alice == eve);
	REQUIRE(!(alice != eve));
	REQUIRE(!(alice < eve));
	REQUIRE(alice <= eve);
	REQUIRE(!(alice > eve));
	REQUIRE(alice >= eve);
}

/* const tests */

TEST_CASE("set const type", "[set]") {
	std::vector<int> v{0, 1, 2, 3, 4, 5};
	const NS::set<int> s(v.begin(), v.end());

	REQUIRE(s.count(0) == 1);

	NS::set<int>::const_iterator it = s.find(3);
	(void)it;
	REQUIRE(s.count(3) == 1);

	REQUIRE(s.lower_bound(3) == s.find(3));
	REQUIRE(s.upper_bound(3) == s.find(4));
	REQUIRE(s.equal_range(3) == NS::make_pair(s.find(3), s.find(4)));
	std::allocator<int> alloc = s.get_allocator();
	(void)alloc;
	NS::less<int> l = s.key_comp();
	l = s.value_comp();
	REQUIRE(!s.empty());
	REQUIRE(s.size() == v.size());
	s.max_size();
	s.begin();
	s.end();
	s.rbegin();
	s.rend();
}
