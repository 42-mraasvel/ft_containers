#ifndef TESTING_HPP
# define TESTING_HPP

# include <string>

namespace Testing {

#define MILLION 1000000

/* Benchmarking */
typedef void (*TestFnc_t)();

void BenchmarkTest(TestFnc_t tester, const std::string& name, const std::string& name_space);

/* Vector */
void VectorTests();

/* Map */
void MapTests();

}


#endif /* TESTING_HPP */
