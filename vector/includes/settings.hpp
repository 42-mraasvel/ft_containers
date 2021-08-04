#ifndef SETTINGS_HPP
# define SETTINGS_HPP

#ifdef STD_VECTOR_TESTS
# include <vector>
typedef std::vector<int> VectorType;
#else
# include "vector.hpp"
typedef ft::vector<int> VectorType;
#endif /* STD_VECTOR_TESTS */

#endif /* SETTINGS_HPP */
