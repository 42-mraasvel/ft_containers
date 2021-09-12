#include "settings.hpp"

#include <vector>

#include "enable_if.hpp"
#include "is_integral.hpp"
#include "equal.hpp"
#include "lexicographical_compare.hpp"
#include "pair.hpp"
#include "make_pair.hpp"
#include "reverse_iterator.hpp"

#ifdef CATCH_TEST_ENABLED
#include "catch.hpp"


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


static bool predicateExample(const int& a, const int& b) {
	return a == b;
}

TEST_CASE("equal: simple tests", "[equal]") {
	std::vector<int> v(5, 5);
	std::vector<int> v2(5, 10);

	REQUIRE(NS::equal(v.begin(), v.end(), v.begin()) == true);
	REQUIRE(NS::equal(v.begin(), v.end(), v.begin(), predicateExample) == true);
	REQUIRE(NS::equal(v.begin(), v.end(), v2.begin()) == false);
	REQUIRE(NS::equal(v.begin(), v.end(), v2.begin(), predicateExample) == false);

	std::vector<std::string> v3;
	v3.push_back("abcde");
	v3.push_back("abc");
	REQUIRE(NS::equal(v3.begin(), v3.end(), v3.begin()) == true);
}

static bool compExampleLC(const char& a, const char& b) {
	return a < b;
}

TEST_CASE("lexicographical_compare: simple tests", "[lexicographical_compare]") {
	std::string s("a");
	std::string s2("aa");

	REQUIRE(NS::lexicographical_compare(s.begin(), s.end(),
			s2.begin(), s2.end()) == true);
	REQUIRE(NS::lexicographical_compare(s2.begin(), s2.end(),
			s.begin(), s.end()) == false);
	REQUIRE(NS::lexicographical_compare(s.begin(), s.end(),
			s.begin(), s.end()) == false);

	REQUIRE(NS::lexicographical_compare(s.begin(), s.end(),
			s2.begin(), s2.end(), compExampleLC) == true);
	REQUIRE(NS::lexicographical_compare(s2.begin(), s2.end(),
			s.begin(), s.end(), compExampleLC) == false);
	REQUIRE(NS::lexicographical_compare(s.begin(), s.end(),
			s.begin(), s.end(), compExampleLC) == false);
}

/*
	PAIR
*/

TEST_CASE("pair constructors", "[pair]") {
	NS::pair<std::string, int> product1;
	NS::pair<std::string, int> product2("tomatoes", 2);
	NS::pair<std::string, int> product3(product2);

	product1.first = "shoes";
	product1.second = 39;

	REQUIRE(product1.first == "shoes");
	REQUIRE(product1.second == 39);
	REQUIRE(product2.first == "tomatoes");
	REQUIRE(product2.second == 2);
	REQUIRE(product3.first == "tomatoes");
	REQUIRE(product3.second == 2);
}

TEST_CASE("pair assignment", "[pair]") {
	NS::pair<int, int> p1(1, 2);
	NS::pair<int, int> p2;

	p2 = p1;
	REQUIRE(p2.first == p1.first);
	REQUIRE(p2.second == p1.second);
}

TEST_CASE("pair relational operators", "[pair]") {
	NS::pair<int,char> foo (10,'z');
	NS::pair<int,char> bar (90,'a');

	REQUIRE(!(foo == bar));
	REQUIRE(foo != bar);
	REQUIRE(foo < bar);
	REQUIRE(!(foo > bar));
	REQUIRE(foo <= bar);
	REQUIRE(!(foo >= bar));
}

TEST_CASE("make pair simple test", "[make_pair]") {
	NS::pair<int, int> p = NS::make_pair(10, 'A');

	REQUIRE(p.first == 10);
	REQUIRE(p.second == static_cast<int>('A'));
}

/*
Reverse Iterator
*/

TEST_CASE("reverse iterator", "[reverse_iterator]") {
	int table[] = {1, 2, 3, 4, 5};

	NS::reverse_iterator<int*> begin(table + sizeof(table) / sizeof(int));
	NS::reverse_iterator<int*> end(table);

	REQUIRE(begin - end == -5);
	REQUIRE(end - begin == 5);

	// Addition and subtraction tests
	REQUIRE(*(1 + begin) == 4);
	REQUIRE(*(begin + 1) == 4);
	REQUIRE(begin[1] == 4);
	REQUIRE(*(end - 1) == 1);

	int i = 5;
	while (begin != end) {
		REQUIRE(*begin++ == i--);
	}
	REQUIRE(begin == end);
	REQUIRE(begin - end == 0);
	REQUIRE(end - begin == 0);
}

#endif
