#include "set.hpp"
#include "settings.hpp"

#ifdef CATCH_TEST_ENABLED
# include "catch.hpp"

/* Constructors */

TEST_CASE("set default constructor", "[set]") {
	NS::set<int> s;

	REQUIRE(s.empty() == true);
	REQUIRE(s.size() == 0);
}

/* Assignmet */

/* Iterators */

/* Capacity */

/* Modifiers */

/* Observers */

/* Operations */

#endif /* CATCH_TEST_ENABLED */

