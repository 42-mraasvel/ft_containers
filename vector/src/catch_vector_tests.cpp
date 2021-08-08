#ifdef CATCH_TEST_ENABLED

#include "settings.hpp"
#include "proto.hpp"
#include "utils.hpp"
#include "catch2/catch.hpp"
#include "vector.hpp"
#include <stdexcept>
#include <memory>
#include <typeinfo>

#include <iostream>

/* Member Types */

/* Constructors */
TEST_CASE("vector default constructor", "[vector]") {
	const VectorInt_t v;
	REQUIRE(v.size() == 0);
	REQUIRE(v.capacity() == 0);
}

TEST_CASE("vector fill constructor", "[vector]") {
	const VectorInt_t v(5, 100);
	REQUIRE(v.size() == 5);
	for (VectorInt_t::size_type i(0); i < v.size(); ++i) {
		REQUIRE(v[i] == 100);
	}

	const VectorInt_t v2(1);
	REQUIRE(v2.size() == 1);
	REQUIRE(v2[0] == 0);

	const VectorInt_t v3(10, 420);
	REQUIRE(v3.size() == 10);
	for (VectorInt_t::size_type i(0); i < v.size(); ++i) {
		REQUIRE(v3[i] == 420);
	}
}

/* Destructor */

TEST_CASE("vector destructor", "[vector]") {
	VectorInt_t v;

	{
		VectorInt_t v2;
		v2 = v;
		VectorInt_t v3(v);
	}

	VectorInt_t* vptr = new VectorInt_t();
	delete vptr;
}

/* Assignment Opeartor */

TEST_CASE("vector assignment operator= #1", "[vector]") {
	VectorInt_t v(5, 5);
	VectorInt_t v2;
	v.reserve(20);
	v2 = v;
	REQUIRE(v2.capacity() == 5);
	REQUIRE(v2.size() == 5);
	for (VectorInt_t::size_type i = 0; i < v2.size(); ++i) {
		REQUIRE(v2[i] == 5);
	}
}

TEST_CASE("vector assignment operator= #2", "[vector]") {
	VectorInt_t v(5, 5);
	VectorInt_t v2(2, 2);
	v.reserve(20);
	v = v2;
	REQUIRE(v.capacity() == 20);
	REQUIRE(v.size() == 2);
	for (VectorInt_t::size_type i = 0; i < v2.size(); ++i) {
		REQUIRE(v2[i] == 2);
	}
}

/* Iterators */

/* Capacity */

TEST_CASE("vector size", "[vector]") {
	VectorInt_t v;

	REQUIRE(v.size() == 0);
	v.push_back(1);
	REQUIRE(v.size() == 1);
}

TEST_CASE("vector max_size", "[vector]") {
	VectorInt_t v;
	std::allocator<int> alloc;
	REQUIRE(v.max_size() == alloc.max_size());
}

TEST_CASE("vector resize #1", "[vector]") {
	VectorInt_t v;
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
	VectorInt_t v(1);
	REQUIRE(v.size() == 1);
	REQUIRE(v.capacity() == 1);
	v.resize(1000);
	REQUIRE(v.size() == 1000);
	REQUIRE(v.capacity() == 1000);
}


TEST_CASE("vector capacity", "[vector]") {
	VectorInt_t v;

	REQUIRE(v.capacity() == 0);
	v.reserve(10);
	REQUIRE(v.capacity() == 10);
	v.reserve(5);
	REQUIRE(v.capacity() == 10);
}

TEST_CASE("vector empty", "[vector]") {
	VectorInt_t v;
	REQUIRE(v.size() == 0);
	REQUIRE(v.empty());
}

TEST_CASE("vector reserve", "[vector]") {
	VectorInt_t v(2, 5);
	v.reserve(1);
	REQUIRE(v.capacity() == 2);

	v.reserve(3);
	REQUIRE(v.size() == 2);
	REQUIRE(v.capacity() == 3);
	for (VectorInt_t::size_type i = 0; i < v.size(); ++i) {
		REQUIRE(v[i] == 5);
	}
}

/* Element access */

TEST_CASE("vector operator[]", "[vector]") {
	VectorInt_t v (4);

	VectorInt_t::size_type sz = v.size();

	// assign some values:
	for (VectorInt_t::size_type i = 0; i < sz; ++i) {
		v[i] = i;
	}

	// reverse vector using operator[]:
	for (VectorInt_t::size_type i = 0; i < sz / 2; ++i)
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
	VectorInt_t v;

	try {
		v.at(1) = 1;
	} catch (const std::out_of_range&) {}
	v.resize(10);
	v.at(9) = 10;
	REQUIRE(v.at(9) == 10);
	REQUIRE(v[9] == 10);
	const VectorInt_t& v2 = v;
	v.at(1) = 42;
	REQUIRE(v2.at(1) == 42);
}

TEST_CASE("vector front", "[vector]") {
	VectorInt_t v(10, 42);
	REQUIRE(&v.front() == &v[0]);
	REQUIRE(v.front() == 42);
	v.at(0) = 1;
	REQUIRE(v.front() == 1);

	const VectorInt_t& v2 = v;
	REQUIRE(v2.front() == v.front());
	REQUIRE(&v2.front() == &v.front());
}

TEST_CASE("vector back", "[vector]") {
	VectorInt_t v(10, 42);

	REQUIRE(v.back() == v[9]);
	REQUIRE(&v.back() == &v[9]);
	v.at(9) = 1;
	REQUIRE(v.back() == 1);

	const VectorInt_t& v2 = v;
	REQUIRE(v2.back() == v.back());
	REQUIRE(&v2.back() == &v.back());
}

/* Modifiers */

TEST_CASE("vector assign fill", "[vector]") {
	VectorInt_t v;
	v.assign(7, 100);
	REQUIRE(v.size() == 7);
	REQUIRE(v.capacity() == 7);
	for (VectorInt_t::size_type i = 0; i < v.size(); ++i) {
		REQUIRE(v[i] == 100);
	}

	VectorInt_t v2(100);
	v2.assign(7, 100);
	REQUIRE(v2.size() == 7);
	REQUIRE(v2.capacity() == 100);

	VectorInt_t v3(3);
	v3.assign(7, 100);
	REQUIRE(v3.size() == 7);
	REQUIRE(v3.capacity() == 7);

	VectorInt_t v4(4);
	v4.assign(7, 100);
	REQUIRE(v4.size() == 7);
	REQUIRE(v4.capacity() == 7);
}

TEST_CASE("vector push_back #1", "[vector]") {
	VectorInt_t v;
	REQUIRE(v.size() == 0);
	REQUIRE(v.capacity() == 0);
	v.push_back(1);
	REQUIRE(v.size() == 1);
	REQUIRE(v[0] == 1);
}

TEST_CASE("vector push_back #2", "[vector]") {
	VectorInt_t v(10, 5);
	REQUIRE(v.size() == 10);
	REQUIRE(v.capacity() == 10);
	for (int i = 0; i < 50; ++i) {
		v.push_back(42);
	}
	REQUIRE(v.size() == 60);
	for (VectorInt_t::size_type i = 10; i < v.size(); ++i) {
		REQUIRE(v[i] == 42);
	}
}

TEST_CASE("vector pop_back", "[vector]") {
	VectorInt_t v;

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

TEST_CASE("vector insert", "[vector]") {

}

TEST_CASE("vector erase", "[vector]") {

}

TEST_CASE("vector swap", "[vector]") {
	VectorInt_t v(3, 100);
	VectorInt_t v2(5, 200);

	v.swap(v2);
	REQUIRE(v.size() == 5);
	REQUIRE(v.capacity() == 5);
	REQUIRE(v2.size() == 3);
	REQUIRE(v2.capacity() == 3);
}

TEST_CASE("vector clear", "[vector]") {
	VectorInt_t v(10);
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

/* Relational Operators */

/* Swap */

#endif /* CATCH_TEST_ENABLED */
