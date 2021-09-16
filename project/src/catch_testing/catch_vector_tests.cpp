#include "settings.hpp"
#include "containers/vector.hpp"

#include "catch.hpp"


/* Constructors */
TEST_CASE("vector default constructor", "[vector]") {
	const NS::vector<int> v;
	REQUIRE(v.size() == 0);
	REQUIRE(v.capacity() == 0);
}

TEST_CASE("vector fill constructor", "[vector]") {
	const NS::vector<int> v(5, 100);
	REQUIRE(v.size() == 5);
	for (NS::vector<int>::size_type i(0); i < v.size(); ++i) {
		REQUIRE(v[i] == 100);
	}

	const NS::vector<int> v2(1);
	REQUIRE(v2.size() == 1);
	REQUIRE(v2[0] == 0);

	const NS::vector<int> v3(10, 420);
	REQUIRE(v3.size() == 10);
	for (NS::vector<int>::size_type i(0); i < v.size(); ++i) {
		REQUIRE(v3[i] == 420);
	}
}

TEST_CASE("vector iterator constructor", "[vector]") {
	NS::vector<int> v(5, 100);

	NS::vector<int> v2(v.begin(), v.end());
	REQUIRE(v == v2);

	int table[] = {5,5,5,5,5};
	NS::vector<int> v3(table, table + sizeof(table) / sizeof(int));
	REQUIRE(v3 == NS::vector<int>(5, 5));
}

TEST_CASE("vector copy constructor", "[vector]") {
	NS::vector<int> v(5, 100);
	NS::vector<int> v2(v);
	REQUIRE(v == v2);
}

/* Destructor */

TEST_CASE("vector destructor", "[vector]") {
	NS::vector<int> v;

	{
		NS::vector<int> v2;
		v2 = v;
		NS::vector<int> v3(v);
	}

	NS::vector<int>* vptr = new NS::vector<int>();
	delete vptr;
}

/* Assignment Opeartor */

TEST_CASE("vector assignment operator= #1", "[vector]") {
	NS::vector<int> v(5, 5);
	NS::vector<int> v2;
	v.reserve(20);
	REQUIRE(v.capacity() == 20);
	REQUIRE(v.size() == 5);
	v2 = v;
	REQUIRE(v2.capacity() == 5);
	REQUIRE(v2.size() == 5);
	for (NS::vector<int>::size_type i = 0; i < v2.size(); ++i) {
		REQUIRE(v2[i] == 5);
	}
}

TEST_CASE("vector assignment operator= #2", "[vector]") {
	NS::vector<int> v(5, 5);
	NS::vector<int> v2(2, 2);
	v.reserve(20);
	v = v2;
	REQUIRE(v.capacity() == 20);
	REQUIRE(v.size() == 2);
	for (NS::vector<int>::size_type i = 0; i < v2.size(); ++i) {
		REQUIRE(v2[i] == 2);
	}
}

/* Iterators */

TEST_CASE("vector iterator assignments", "[vector]") {
	NS::vector<int> v(5, 5);
	const NS::vector<int> v2(5, 5);

	NS::vector<int>::iterator it = v.begin();
	NS::vector<int>::const_iterator itc = v2.begin();
	NS::vector<int>::const_iterator itc2 = v.begin();

	NS::vector<int>::iterator e_it = v.end();
	NS::vector<int>::const_iterator e_itc = v2.end();
	NS::vector<int>::const_iterator e_itc2 = v.end();
	(void)e_itc2;

	REQUIRE(NS::distance(it, e_it) == static_cast<long>(v.size()));
	REQUIRE(NS::distance(itc, e_itc) == static_cast<long>(v.size()));
	REQUIRE(it == itc2);
	REQUIRE(it != itc);
}

TEST_CASE("vector reverse iterator", "[vector]") {
	NS::vector<int> v;
	for (int i = 0; i < 5; ++i) {
		v.push_back(i);
	}
	v.push_back(42);

	NS::vector<int>::reverse_iterator it = v.rbegin();
	REQUIRE(*it == 42);
	it++;

	int i = 4;
	while (it != v.rend()) {
		REQUIRE(*it == i);
		--i;
		++it;
	}

	const NS::vector<int> v2(v);

	NS::vector<int>::const_reverse_iterator begin_v2 = v2.rbegin();
	NS::vector<int>::const_reverse_iterator end_v2 = v2.rend();
	NS::vector<int>::reverse_iterator begin_v = v.rbegin();
	REQUIRE(std::equal(begin_v2, end_v2, begin_v));

	REQUIRE(NS::vector<int>::const_reverse_iterator(v.rbegin()) == NS::vector<int>::reverse_iterator(v.rbegin()));

}

/* Capacity */

TEST_CASE("vector size", "[vector]") {
	NS::vector<int> v;

	REQUIRE(v.size() == 0);
	v.push_back(1);
	REQUIRE(v.size() == 1);
}

TEST_CASE("vector max_size", "[vector]") {
	NS::vector<int> v;
	std::allocator<int> alloc;
	REQUIRE(v.max_size() == alloc.max_size());
}

TEST_CASE("vector resize #1", "[vector]") {
	NS::vector<int> v;
	REQUIRE(v.empty());

	REQUIRE(v.capacity() == 0);
	v.resize(100);
	REQUIRE(v.capacity() == 100);
	REQUIRE(v.size() == 100);

	v.resize(20);
	REQUIRE(v.size() == 20);
	REQUIRE(v.capacity() == 100);

	v.resize(101);
	REQUIRE(v.size() == 101);
}

TEST_CASE("vector resize #2", "[vector]") {
	NS::vector<int> v(1);
	REQUIRE(v.size() == 1);
	REQUIRE(v.capacity() == 1);
	v.resize(1000);
	REQUIRE(v.size() == 1000);
	REQUIRE(v.capacity() == 1000);
}


TEST_CASE("vector capacity", "[vector]") {
	NS::vector<int> v;

	REQUIRE(v.capacity() == 0);
	v.reserve(10);
	REQUIRE(v.capacity() == 10);
	v.reserve(5);
	REQUIRE(v.capacity() == 10);
}

TEST_CASE("vector empty", "[vector]") {
	NS::vector<int> v;
	REQUIRE(v.size() == 0);
	REQUIRE(v.empty());
}

TEST_CASE("vector reserve", "[vector]") {
	NS::vector<int> v(2, 5);
	v.reserve(1);
	REQUIRE(v.capacity() == 2);

	v.reserve(3);
	REQUIRE(v.size() == 2);
	REQUIRE(v.capacity() == 3);
	for (NS::vector<int>::size_type i = 0; i < v.size(); ++i) {
		REQUIRE(v[i] == 5);
	}
}

/* Element access */

TEST_CASE("vector operator[]", "[vector]") {
	NS::vector<int> v (4);

	NS::vector<int>::size_type sz = v.size();

	// assign some values:
	for (NS::vector<int>::size_type i = 0; i < sz; ++i) {
		v[i] = i;
	}

	// reverse vector using operator[]:
	for (NS::vector<int>::size_type i = 0; i < sz / 2; ++i)
	{
		int temp;
		temp = v[sz - 1 - i];
		v[sz - 1 - i] = v[i];
		v[i] = temp;
	}

	REQUIRE(v.size() == 4);
	REQUIRE(v[0] == 3);
	REQUIRE(v[1] == 2);
	REQUIRE(v[2] == 1);
	REQUIRE(v[3] == 0);
}

TEST_CASE("vector at", "[vector]") {
	NS::vector<int> v;

	try {
		v.at(1) = 1;
	} catch (const std::out_of_range&) {}
	v.resize(10);
	v.at(9) = 10;
	REQUIRE(v.at(9) == 10);
	REQUIRE(v[9] == 10);
	const NS::vector<int>& v2 = v;
	v.at(1) = 42;
	REQUIRE(v2.at(1) == 42);
}

TEST_CASE("vector front", "[vector]") {
	NS::vector<int> v(10, 42);
	REQUIRE(&v.front() == &v[0]);
	REQUIRE(v.front() == 42);
	v.at(0) = 1;
	REQUIRE(v.front() == 1);

	const NS::vector<int>& v2 = v;
	REQUIRE(v2.front() == v.front());
	REQUIRE(&v2.front() == &v.front());
}

TEST_CASE("vector back", "[vector]") {
	NS::vector<int> v(10, 42);

	REQUIRE(v.back() == v[9]);
	REQUIRE(&v.back() == &v[9]);
	v.at(9) = 1;
	REQUIRE(v.back() == 1);

	const NS::vector<int>& v2 = v;
	REQUIRE(v2.back() == v.back());
	REQUIRE(&v2.back() == &v.back());
}

/* Modifiers */

TEST_CASE("vector assign fill", "[vector]") {
	NS::vector<int> v;
	v.assign(7, 100);
	REQUIRE(v.size() == 7);
	REQUIRE(v.capacity() == 7);
	for (NS::vector<int>::size_type i = 0; i < v.size(); ++i) {
		REQUIRE(v[i] == 100);
	}

	NS::vector<int> v2(100);
	v2.assign(7, 100);
	REQUIRE(v2.size() == 7);
	REQUIRE(v2.capacity() == 100);

	NS::vector<int> v3(3);
	v3.assign(7, 100);
	REQUIRE(v3.size() == 7);
	REQUIRE(v3.capacity() == 7);

	NS::vector<int> v4(4);
	v4.assign(7, 100);
	REQUIRE(v4.size() == 7);
	REQUIRE(v4.capacity() == 7);
}

TEST_CASE("vector assign iterator", "[vector]") {
	NS::vector<int> v;

	v.assign(7, 100);
	REQUIRE(v.size() == 7);
	NS::vector<int> v2;
	v2.assign(v.begin(), v.end());
	REQUIRE(v2.size() == 7);
	REQUIRE(v == v2);

	NS::vector<int> v3;
	v3.assign(100, 250);
	REQUIRE(v3.size() == 100);
	v3.assign(v2.begin(), v2.end());
	REQUIRE(v3.size() == 7);
	REQUIRE(v3.capacity() == 100);
	REQUIRE(v3 == v);
}

TEST_CASE("vector push_back #1", "[vector]") {
	NS::vector<int> v;
	REQUIRE(v.size() == 0);
	REQUIRE(v.capacity() == 0);
	v.push_back(1);
	REQUIRE(v.size() == 1);
	REQUIRE(v[0] == 1);
}

TEST_CASE("vector push_back #2", "[vector]") {
	NS::vector<int> v(10, 5);
	REQUIRE(v.size() == 10);
	REQUIRE(v.capacity() == 10);
	for (int i = 0; i < 50; ++i) {
		v.push_back(42);
	}
	REQUIRE(v.size() == 60);
	for (NS::vector<int>::size_type i = 10; i < v.size(); ++i) {
		REQUIRE(v[i] == 42);
	}
}

TEST_CASE("vector pop_back", "[vector]") {
	NS::vector<int> v;

	v.push_back(10);
	REQUIRE(v.size() == 1);
	v.pop_back();
	REQUIRE(v.size() == 0);
	v.push_back(1);
	v.push_back(2);
	REQUIRE(v.back() == 2);
	v.pop_back();
	REQUIRE(v.back() == 1);
}

TEST_CASE("vector insert single element", "[vector]") {
	NS::vector<int> v(5, 10);

	NS::vector<int>::iterator it;

	REQUIRE(v.size() == 5);
	it = v.insert(v.begin() + 1, 1);
	REQUIRE(v[1] == 1);
	REQUIRE(*it == 1);
	REQUIRE(&(*it) == &v[1]);
	REQUIRE(v.size() == 6);

	v.insert(v.end(), 2);
	REQUIRE(v.back() == 2);

	v.insert(v.begin(), 3);
	REQUIRE(v.front() == 3);
}

TEST_CASE("vector insert fill", "[vector]") {
	NS::vector<int> v(5, 10);

	v.insert(v.end(), 10, 42);
	REQUIRE(v.size() == 15);
	REQUIRE(v.back() == 42);

	v.insert(v.begin(), 50, 100);
	REQUIRE(v.size() == 65);
	REQUIRE(v.front() == 100);

	v.insert(v.begin() + 5, 1000, 1);
	REQUIRE(v[10] == 1);
	REQUIRE(v.size() == 1065);
}

TEST_CASE("vector insert range", "[vector]") {
	NS::vector<int> v(5, 5);

	NS::vector<int> v2;
	v2.push_back(1);
	v2.push_back(2);
	v2.push_back(3);

	v.insert(v.begin(), v2.begin(), v2.end());
	REQUIRE(v[0] == 1);
	REQUIRE(v[1] == 2);
	REQUIRE(v[2] == 3);
	REQUIRE(v.size() == 8);
	v.insert(v.end(), v2.begin(), v2.end());
	REQUIRE(v.size() == 11);
	v.insert(v.begin() + 4, v2.begin(), v2.end());
	REQUIRE(v.size() == 14);
}

TEST_CASE("vector erase single", "[vector]") {
	NS::vector<int> v;
	for (int i = 0; i < 5; ++i) {
		v.push_back(i + 1);
	}

	v.erase(v.end() - 1);
	REQUIRE(v.back() == 4);
	v.erase(v.begin());
	REQUIRE(v.front() == 2);
	REQUIRE(v.size() == 3);
}

TEST_CASE("vector erase multiple", "[vector]") {
	NS::vector<int> v(100, 1);

	REQUIRE(v.size() == 100);
	v.erase(v.begin(), v.end());
	REQUIRE(v.size() == 0);
	REQUIRE(v.capacity() == 100);
	for (int i = 0; i < 5; ++i) {
		v.push_back(i + 1);
	}

	v.erase(v.begin(), v.begin() + 4);
	REQUIRE(v.size() == 1);
	REQUIRE(v.front() == 5);
	REQUIRE(v.back() == 5);
}

TEST_CASE("vector swap", "[vector]") {
	NS::vector<int> v(3, 100);
	NS::vector<int> v2(5, 200);

	v.swap(v2);
	REQUIRE(v.size() == 5);
	REQUIRE(v.capacity() == 5);
	REQUIRE(v2.size() == 3);
	REQUIRE(v2.capacity() == 3);
}

TEST_CASE("vector clear", "[vector]") {
	NS::vector<int> v(10);
	REQUIRE(v.size() == 10);
	REQUIRE(v.capacity() == 10);
	v.clear();
	REQUIRE(v.size() == 0);
	REQUIRE(v.capacity() == 10);
}

/* Allocator */
TEST_CASE("vector get_allocator", "[vector]") {
	ft::vector<int> v;
	std::vector<int> v2;

	const std::type_info& ti = typeid(v.get_allocator());
	const std::type_info& expected = typeid(v2.get_allocator());

	REQUIRE(ti.name() == expected.name());
}

/* Non-member function overloads */

TEST_CASE("vector swap non-member", "[vector]") {
	NS::vector<int> v(10, 10);
	NS::vector<int> v2(42, 42);

	REQUIRE(v.size() == 10);
	REQUIRE(v2.size() == 42);
	swap(v, v2);
	REQUIRE(v.size() == 42);
	REQUIRE(v2.size() == 10);
}

/* Relational Operators */

TEST_CASE("vector relational operators", "[vector]") {
	NS::vector<int> v(3, 100);
	NS::vector<int> v2(2, 200);

	REQUIRE(!(v == v2));
	REQUIRE(v != v2);
	REQUIRE(v < v2);
	REQUIRE(!(v > v2));
	REQUIRE(v <= v2);
	REQUIRE(!(v >= v2));
}

/* Swap */
