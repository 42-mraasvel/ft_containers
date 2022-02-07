# Containers
	Implementation of the following C++ STL data structures:
		- vector
		- map (RB)
		- set (RB)
		- stack

## Known Issues
	1. Exception-safe code:
		leaks when exceptions are thrown in constructors of the templated value.
	2. Sentinel node in RB tree calls the default constructor unnecessarily
	3. the map value_compare has a public constructor
	4. Other functions call the default unnecessarily due to poorly implemented value_comp
