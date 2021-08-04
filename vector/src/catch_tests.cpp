#ifdef CATCH_TEST_ENABLED

#include "proto.hpp"
#include "vector.hpp"
#include "catch2/catch.hpp"

TEST_CASE("ft vector testing", "[vector]") {
	REQUIRE(resize_test());
}

#endif
