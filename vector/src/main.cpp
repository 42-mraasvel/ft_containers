#include "header.hpp"

template <typename C>
void PrintCapSize(const C& container) {
	std::cout << "SIZE(" << container.size() << ')' << std::endl;
	std::cout << "CAP(" << container.capacity() << ')' << std::endl;
	std::cout << std::endl;
}

template <typename C>
void PrintContainer(const C& container) {
	PrintCapSize(container);
	std::cout << "contains:";
	for (typename C::size_type i = 0; i < container.size(); ++i) {
		std::cout << ' ' << container[i];
	}
	std::cout << '$' << std::endl;
}

class LeakingClass {
public:
	LeakingClass() {
		p = new int;
	}

	LeakingClass(const LeakingClass& from) {
		p = NULL;
		*this = from;
	}


	LeakingClass& operator=(const LeakingClass& rhs) {
		if (p)
			delete p;
		p = new int(*rhs.p);
		return *this;
	}

	~LeakingClass() {
		delete p;
	}
private:
	int* p;
};

#ifndef CATCH_TEST_ENABLED
int main() {

	ft::vector<int> v(1000, 10);
	ft::vector<int> v2(10, 1000);

	PrintCapSize(v);
	PrintCapSize(v2);

	v.swap(v2);
	PrintCapSize(v);
	PrintCapSize(v2);

	return 0;
}
#endif
