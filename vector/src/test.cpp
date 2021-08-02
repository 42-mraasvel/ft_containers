#include "settings.hpp"
#include "proto.hpp"

#ifdef DEBUG
#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

TEST_CASE("ft vector testing", "[vector]") {
	REQUIRE(Factorial(0) == 1);
}

#endif
