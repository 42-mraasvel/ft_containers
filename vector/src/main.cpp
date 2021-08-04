#include "header.hpp"

template <typename C>
void PrintCapSize(const C& container) {
	std::cout << "SIZE(" << container.size() << ')' << std::endl;
	std::cout << "CAP(" << container.capacity() << ')' << std::endl;
}

#ifndef CATCH_TEST_ENABLED
int main() {
	ft::vector<int> myvector;
	for (int i = 1; i < 10; ++i) {
		myvector.push_back(i);
	}

	myvector.resize(5);
	myvector.resize(8,100);
	myvector.resize(12);

	std::cout << "myvector contains:";
	for (size_t i = 0; i < myvector.size(); ++i) {
		std::cout << ' ' << myvector[i];
	}
	std::cout << '\n';

	return 0;
}
#endif
