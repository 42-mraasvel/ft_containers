#include "header.hpp"

template <typename C>
void PrintCapSize(const C& container) {
	std::cout << "SIZE(" << container.size() << ')' << std::endl;
	std::cout << "CAP(" << container.capacity() << ')' << std::endl;
	std::cout << std::endl;
}

template <typename C>
void PrintContainer(const C& container) {
	std::cout << "contains:";
	for (typename C::size_type i = 0; i < container.size(); ++i) {
		std::cout << ' ' << container[i];
	}
	std::cout << '$' << std::endl;
	PrintCapSize(container);
}

class LeakingClass {
public:
	LeakingClass() {
		p = new int;
	}

	LeakingClass(const LeakingClass& from)
	: p(NULL) {
		*this = from;
	}


	LeakingClass& operator=(const LeakingClass& rhs) {
		if (p)
			delete p;
		p = new int(*rhs.p);
		// p = rhs.p;
		return *this;
	}

	~LeakingClass() {
		delete p;
	}
private:
	int* p;
};

class Lmao : public std::iterator_traits<int*> {

};

#ifndef CATCH_TEST_ENABLED
int main() {

	ft::vector<int> v;

	for (int i = 0; i < 5; ++i) {
		v.push_back(i + 1);
	}

	PrintContainer(v);

	ft::vector<int> v2(v.begin(), v.end());
	ft::vector<int> v3(1, 2);

	PrintContainer(v2);

	return 0;
}
#endif
