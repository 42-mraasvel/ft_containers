#include "header.hpp"

template <typename C>
void PrintCapSize(const C& container) {
	std::cout << "SIZE(" << container.size() << ')' << std::endl;
	std::cout << "CAP(" << container.capacity() << ')' << std::endl;
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

	ft::vector<LeakingClass> v(1);

	return 0;
}
#endif
