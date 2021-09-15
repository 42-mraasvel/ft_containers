#include "settings.hpp"
#include "testing.hpp"

#include "containers/vector.hpp"
#include <vector>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <cstdlib>


namespace Testing {

void BenchmarkTest(TestFnc_t tester, const std::string& name, const std::string& name_space) {
	tester();
	std::clock_t begin = std::clock();
	tester();
	std::clock_t end = std::clock();
	double elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
	std::cout << name << "(" << std::setw(3) << name_space << ") " << elapsed_seconds << std::endl;
	// Benchmark<ft::vector>(tester, name, "ft");
	// Benchmark<std::vector>(tester, name, "std");
}

}


#ifndef USING_CATCH
int main() {

	srand(time(NULL));

	Testing::VectorTests();
	Testing::MapTests();

	// std::vector<int> v;

	// for (int i = 0; i < 16; ++i) {
	// 	v.push_back(i);
	// 	std::cout << v.capacity() << std::endl;
	// }
	return 0;
}
#endif /* USING_CATCH */
