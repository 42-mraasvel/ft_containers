#ifndef SETTINGS_HPP
# define SETTINGS_HPP

#ifdef STD_VECTOR_TESTS
# include <vector>
typedef std::vector<int> VectorInt_t;
#else
# include "vector.hpp"
typedef ft::vector<int> VectorInt_t;
#endif /* STD_VECTOR_TESTS */

#endif /* SETTINGS_HPP */
