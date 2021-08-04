
#ifdef CATCH_TEST_ENABLED

#include "settings.hpp"
#include <iostream>

bool resize_test() {

	VectorType myvector;
	for (int i = 1; i < 10; ++i) {
		myvector.push_back(i);
	}

	myvector.resize(5);
	myvector.resize(8,100);
	myvector.resize(12);

	// Expected:
	// 1 2 3 4 5 100 100 100 0 0 0 0
	VectorType expected_vector(12);
	for (int i = 0; i < 5; ++i) {
		expected_vector[i] = i + 1;
	}
	expected_vector[5] = 100;
	expected_vector[6] = 100;
	expected_vector[7] = 100;

	for (size_t i(0); i < expected_vector.size(); ++i) {
		if (expected_vector[i] != myvector[i]) {
			return false;
		}
	}

	if (expected_vector.size() != myvector.size()) {
		return false;
	}

	if (expected_vector.capacity() != myvector.capacity()) {
		return false;
	}

	return true;
}


#endif
