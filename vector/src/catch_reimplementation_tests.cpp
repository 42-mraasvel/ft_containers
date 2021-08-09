#ifdef CATCH_TEST_ENABLED

#include "settings.hpp"
#include "catch2/catch.hpp"

#include "enable_if.hpp"
#include "is_integral.hpp"
#include "equal.hpp"

/*
**
**	NAMESPACE: # define NS ft/std depending on what is being tested
**	Use NS:: to test difference betwen ft:: and std:: functionalities
*/

TEST_CASE("enable_if", "[enable_if]") {
	REQUIRE(sizeof(NS::enable_if<true, int>::type) == sizeof(int));
}

/*
is_integral supported fundamental types:
	https://www.cplusplus.com/reference/type_traits/is_integral/
*/
TEST_CASE("is_integral: TRUE tests", "[is_integral]") {
	REQUIRE (NS::is_integral<bool>::value == true);
	REQUIRE (NS::is_integral<char>::value == true);
	REQUIRE (NS::is_integral<wchar_t>::value == true);
	REQUIRE (NS::is_integral<signed char>::value == true);
	REQUIRE (NS::is_integral<short int>::value == true);
	REQUIRE (NS::is_integral<int>::value == true);
	REQUIRE (NS::is_integral<long int>::value == true);
	REQUIRE (NS::is_integral<unsigned char>::value == true);
	REQUIRE (NS::is_integral<unsigned short int>::value == true);
	REQUIRE (NS::is_integral<unsigned int>::value == true);
	REQUIRE (NS::is_integral<unsigned long int>::value == true);
}

TEST_CASE("is_integral: FALSE tests", "[is_integral]") {
	REQUIRE (NS::is_integral<std::string>::value == false);
	REQUIRE (NS::is_integral<float>::value == false);
	REQUIRE (NS::is_integral<double>::value == false);
	REQUIRE (NS::is_integral<long double>::value == false);
	REQUIRE (NS::is_integral<void>::value == false);
	REQUIRE (NS::is_integral<NS::is_integral<void>>::value == false);
}



#endif
