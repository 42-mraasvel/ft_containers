
#ifdef CATCH_TEST_ENABLED

#include "settings.hpp"
#include "proto.hpp"
#include "utils.hpp"
#include "catch2/catch.hpp"
#include "vector.hpp"

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
	const VectorInt_t v2(1);

	REQUIRE(v.size() == 5);
	for (VectorInt_t::size_type i(0); i < v.size(); ++i) {
		REQUIRE(v[i] == 100);
	}

	REQUIRE(v2.size() == 1);
	REQUIRE(v2[0] == 0);
}


/* Destructor */

/* Iterators */

/* Capacity */

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

/* Modifiers */

/* Allocator */


#endif
