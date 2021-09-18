#include "testing.hpp"

#include "containers/vector.hpp"
#include <vector>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <cstdlib>


namespace Testing {

double BenchmarkTest(TestFnc_t tester, const std::string& name, const std::string& name_space) {

	static const double EPSILON = 1e-06;

	tester();
	std::clock_t begin = std::clock();
	tester();
	std::clock_t end = std::clock();
	double elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
	if (elapsed_seconds < EPSILON) {
		std::cout << name << "(" << std::setw(3) << name_space << ") " << 0 << std::endl;
	} else {
		std::cout << name << "(" << std::setw(3) << name_space << ") " << elapsed_seconds << std::endl;
	}

	return elapsed_seconds;
}

void Benchmarking() {
	std::cout << "  ***** VECTOR BENCHMARK TESTS *****  " << std::endl;
	VectorTests();
	std::cout << std::endl << "  ***** MAP BENCHMARK TESTS *****  " << std::endl;
	MapTests();
	std::cout << std::endl << "  ***** SET BENCHMARK TESTS *****  " << std::endl;
	SetTests();
}

}

#ifndef USING_CATCH
int main() {

	srand(time(NULL));
	Testing::Benchmarking();

	return 0;
}
#endif /* USING_CATCH */
