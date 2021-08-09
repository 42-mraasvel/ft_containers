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

template <typename T1, typename T2>
void printPair(ft::pair<T1, T2> p) {
	std::cout << '|' << p.first << " : " << p.second << '|' << std::endl;
}

#ifndef CATCH_TEST_ENABLED
int main() {

	ft::pair<int, std::string> p;

	printPair(p);

	ft::pair<std::string, std::string> p2("ab", "abc");
	printPair(p2);
	ft::pair<std::string, std::string> p3(p2);
	printPair(p3);
	return 0;
}
#endif
