#include "map.hpp"
#include "settings.hpp"

#ifdef CATCH_TEST_ENABLED
#include "catch2/catch.hpp"

/*
CONSTRUCTOR
*/

TEST_CASE("map default constructor", "[map]") {
	NS::map<int, int> m;

	REQUIRE(m.size() == 0);
	REQUIRE(m.empty());
	REQUIRE(m.begin() == m.end());
	REQUIRE(m.rbegin() == m.rend());
	REQUIRE(m.find(1) == m.end());
	REQUIRE(m.lower_bound(1) == m.end());
	REQUIRE(m.upper_bound(1) == m.end());

	auto it_pair = m.equal_range(1);
	REQUIRE(it_pair.first == m.end());
	REQUIRE(it_pair.second == m.end());
}

TEST_CASE("map range constructor", "[map]") {
	NS::map<char, int> m;

	m['a'] = 10;
	m['b'] = 20;
	m['c'] = 30;
	m['d'] = 40;
	m['e'] = 50;

	NS::map<char, int> m2(m.begin(), m.end());
	REQUIRE(m2['a'] == 10);
	REQUIRE(m2['b'] == 20);
	REQUIRE(m2['c'] == 30);
	REQUIRE(m2['d'] == 40);
	REQUIRE(m2['e'] == 50);
}

TEST_CASE("map copy constructor", "[map]") {
	NS::map<char, int> m;

	m['a'] = 10;
	m['b'] = 20;
	m['c'] = 30;
	m['d'] = 40;
	m['e'] = 50;

	NS::map<char, int> m2(m);
	REQUIRE(m2['a'] == 10);
	REQUIRE(m2['b'] == 20);
	REQUIRE(m2['c'] == 30);
	REQUIRE(m2['d'] == 40);
	REQUIRE(m2['e'] == 50);
}

/*
ASSIGNMENT
*/

TEST_CASE("map assignment operator", "[map]") {
	NS::map<char, int> m;

	m['a'] = 10;
	m['b'] = 20;
	m['c'] = 30;
	m['d'] = 40;
	m['e'] = 50;

	NS::map<char, int> m2;

	m2 = m;
	REQUIRE(m2['a'] == 10);
	REQUIRE(m2['b'] == 20);
	REQUIRE(m2['c'] == 30);
	REQUIRE(m2['d'] == 40);
	REQUIRE(m2['e'] == 50);
	m.clear();
	m2 = m;
	REQUIRE(m.size() == 0);
}

/*
ITERATORS
*/

TEST_CASE("map iterator", "[map]") {
	NS::map<int, int> m;

	for (int i = 0; i < 10; ++i) {
		m[i] = i;
	}

	int i = 0;
	NS::map<int, int>::iterator it = m.begin();
	NS::map<int, int>::iterator ite = m.end();
	while (it != ite) {
		REQUIRE(it->first == i);
		REQUIRE(it->second == i);
		++i;
		++it;
	}

	it = m.find(5);
	REQUIRE(it->first == 5);
	++it;
	m.erase(5);
	--it;
	REQUIRE(it->first == 4);
	--ite;
	REQUIRE(ite->first == 9);
	++ite;
	m.erase(m.find(9));
	--ite;
	REQUIRE(ite->first == 8);
}

TEST_CASE("map reverse iterator", "[map]") {
	NS::map<int, int> m;
	for (int i = 0; i < 10; ++i) {
		m[i] = i;
	}

	int i = m.size() - 1;
	auto it = m.rbegin();
	auto ite = m.rend();

	while (it != ite) {
		REQUIRE(it->first == i);
		++it;
		--i;
	}
	--it;
	REQUIRE(it->first == 0);
}

/*
CAPACITY
*/

TEST_CASE("map empty", "[map]") {
	NS::map<int, int> m;

	REQUIRE(m.empty());
	REQUIRE(m.size() == 0);
	m[0] = 0;
	REQUIRE(m.size() != 0);
	REQUIRE(!m.empty());
}

TEST_CASE("map size", "[map]") {
	NS::map<int, int> m;
	for (int i = 0; i < 100; ++i) {
		m[0] = i;
	}

	REQUIRE(m.size() == 1);
	m.clear();
	REQUIRE(m.size() == 0);
	m[0] = 42;
	REQUIRE(m.begin()->first == 0);
	REQUIRE(m.size() == 1);
	m.erase(0);
	REQUIRE(m.size() == 0);
}

/*
ELEMENT ACCESS
*/

TEST_CASE("map operator[]", "[map]") {
	NS::map<std::string, int> m;

	m["hello"] = 42;
	m["TEST"];

	m["test"] = 6;
	REQUIRE(m["test"] == 6);
	m["test"] = 420;
	REQUIRE(m["test"] == 420);

	REQUIRE(m.size() == 3);
	REQUIRE(m.find("hello") != m.end());
	REQUIRE(m["hello"] == 42);
}

/*
MODIFIERS
*/

TEST_CASE("map insert", "[map]") {
	NS::map<char, int> m;

	// Single value
	m.insert(NS::make_pair('a', 100));
	m.insert(NS::make_pair('z', 200));

	NS::pair<NS::map<char, int>::iterator, bool> ret;

	ret = m.insert(NS::make_pair('z', 500));
	REQUIRE(ret.second == false);
	REQUIRE(ret.first->second == 200);

	NS::map<char, int>::iterator it = m.end();
	--it;

	// Hint
	m.insert(it, NS::make_pair('b', 300));
	m.insert(it, NS::make_pair('c', 400));
	REQUIRE(m.size() == 4);

	NS::map<char, int> m2;

	// Range
	m2.insert(m.begin(), m.find('c'));

	REQUIRE(m2.size() == 2);
	REQUIRE(m2['a'] == 100);
	REQUIRE(m2['b'] == 300);
}

TEST_CASE("map erase", "[map]") {
	NS::map<char,int> mymap;
	NS::map<char,int>::iterator it;

	mymap['a'] = 10;
	mymap['b'] = 20;
	mymap['c'] = 30;
	mymap['d'] = 40;
	mymap['e'] = 50;
	mymap['f'] = 60;

	it = mymap.find('b');
	mymap.erase(it); // erasing by iterator

	mymap.erase('c'); // erasing by key

	it = mymap.find('e');
	mymap.erase(it, mymap.end()); // erasing by range

	REQUIRE(mymap.size() == 2);
	REQUIRE(mymap['a'] == 10);
	REQUIRE(mymap['d'] == 40);

	mymap.erase(mymap.begin(), mymap.end());
	REQUIRE(mymap.size() == 0);
	mymap.insert(NS::make_pair('a', 100));
	REQUIRE(std::distance(mymap.begin(), mymap.end()) == 1);
}

TEST_CASE("map swap", "[map]") {
	NS::map<char, int> m1;
	NS::map<char, int> m2;

	m1['a'] = 10;
	m1['b'] = 20;
	m1['c'] = 30;

	m2['x'] = 42;

	m1.swap(m2);

	REQUIRE(m1.size() == 1);
	REQUIRE(m1['x'] == 42);

	REQUIRE(m2.size() == 3);
	REQUIRE(m2['a'] == 10);
	REQUIRE(m2['b'] == 20);
	REQUIRE(m2['c'] == 30);
}

TEST_CASE("map clear", "[map]") {
	NS::map<int, int> m;

	for (int i = 0; i < 100; ++i) {
		m[i] = i;
	}
	REQUIRE(m.size() == 100);
	m.clear();
	REQUIRE(m.size() == 0);
	REQUIRE(m.begin() == m.end());
}

/*
OPERATIONS
*/

TEST_CASE("map find", "[map]") {
	NS::map<char, int> m;

	m['a'] = 50;
	m['b'] = 100;
	m['c'] = 150;
	m['d'] = 200;

	REQUIRE(m.size() == 4);
	NS::map<char, int>::iterator it = m.find('b');
	m.erase(it);
	REQUIRE(m.size() == 3);
	it = m.find('b');
	REQUIRE(it == m.end());
}

TEST_CASE("map count", "[map]") {
	NS::map<char, int> m;

	m['a'] = 1;
	m['c'] = 2;
	m['z'] = 3;

	REQUIRE(m.count('a') == 1);
	REQUIRE(m.count('b') == 0);
	REQUIRE(m.count('c') == 1);
	REQUIRE(m.count('z') == 1);
}

TEST_CASE("map lower_bound", "[map]") {
	NS::map<char, int> mymap;
	NS::map<char, int>::iterator itlow;

	mymap['a'] = 20;
	mymap['b'] = 40;
	mymap['c'] = 60;
	mymap['d'] = 80;
	mymap['e'] = 100;

	itlow = mymap.lower_bound ('b');

	REQUIRE(itlow->first == 'b');
	mymap.erase(itlow);
	itlow = mymap.lower_bound('b');
	REQUIRE(itlow->first == 'c');
	itlow = mymap.lower_bound('f');
	REQUIRE(itlow == mymap.end());
}

TEST_CASE("map upper_bound", "[map]") {
	NS::map<char, int> mymap;
	NS::map<char, int>::iterator itup;

	mymap['a']=20;
	mymap['b']=40;
	mymap['c']=60;
	mymap['d']=80;
	mymap['e']=100;

	itup = mymap.upper_bound ('d'); // itup points to e (not d!)

	REQUIRE(itup->first == 'e');
	itup = mymap.upper_bound('e');
	REQUIRE(itup == mymap.end());
	itup = mymap.upper_bound('f');
	REQUIRE(itup == mymap.end());
	itup = mymap.upper_bound('A');
	REQUIRE(itup->first == 'a');
}

TEST_CASE("map equal_range", "[map]") {
	NS::map<char,int> mymap;

	mymap['a']=10;
	mymap['b']=20;
	mymap['d']=30;

	NS::pair<NS::map<char, int>::iterator, NS::map<char, int>::iterator> ret;
	ret = mymap.equal_range('b');
	REQUIRE(ret.first == mymap.lower_bound('b'));
	REQUIRE(ret.second == mymap.upper_bound('b'));
	ret = mymap.equal_range('c');
	REQUIRE(ret.first == mymap.lower_bound('c'));
	REQUIRE(ret.second == mymap.upper_bound('c'));
}

#endif
