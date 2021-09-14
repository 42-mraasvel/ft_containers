#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft {

template <class T1, class T2>
struct pair {
public:
	typedef T1 first_type;
	typedef T2 second_type;

/* Constructors/Destructors */
	pair()
	: first(), second() {}

	template<class U, class V>
	pair(const pair<U,V>& pr)
	: first(pr.first), second(pr.second) {}

	pair(const first_type& a, const second_type& b)
	: first(a), second(b) {}
	
	~pair() {}

/* Assignment Operator */
	pair& operator=(const pair& rhs) {
		first = rhs.first;
		second = rhs.second;
		return *this;
	}

/* Members */
	first_type first;
	second_type second;

};

template <class T1, class T2>
bool operator==(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
	return (lhs.first == rhs.first) && (lhs.second == lhs.second);
}

template <class T1, class T2>
bool operator!=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
	return !(lhs == rhs);
}

template <class T1, class T2>
bool operator<(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
	return lhs.first < rhs.first \
		|| (!(rhs.first < lhs.first) && lhs.second < rhs.second);
}

template <class T1, class T2>
bool operator<=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
	return !(rhs < lhs);
}

template <class T1, class T2>
bool operator>(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
	return rhs < lhs;
}

template <class T1, class T2>
bool operator>=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
	return !(lhs < rhs);
}

template <class T1, class T2>
pair<T1, T2> make_pair (T1 x, T2 y) {
	return pair<T1, T2>(x, y);
}

}

#endif /* PAIR_HPP */
