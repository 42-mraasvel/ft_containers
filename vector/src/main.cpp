#include "header.hpp"

int Factorial(int n) {
	return n <= 1 ? 1 : n * Factorial(n - 1);
}

typedef std::allocator<int> Alloc;
typedef ft::vector<int> IntVec;

class TestClass {
public:
	TestClass(int n)
		: n(n) {}
	~TestClass() {
		std::cout << "TEST(" << n << ")" << std::endl;
	}
private:
	int n;
};

void PrintType(const std::type_info& ti) {
	std::cout << "TYPE: " << ti.name() << std::endl;
}

#ifndef DEBUG
int main() {
	std::vector<TestClass> v;

	for (int i(0); i < 2; ++i) {
		v.push_back(TestClass(i));
	}
	std::cout << std::endl;
	return 0;
}
#endif
