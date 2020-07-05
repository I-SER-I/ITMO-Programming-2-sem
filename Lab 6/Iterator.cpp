#include <iterator>

template <typename iterator, typename object>
bool all_of(const iterator& begin, const iterator& end, bool(& func)(object)) {
	for (auto it = begin; it != end; it = std::next(it))
		if (!func(*it))
			return false;
	return true;
}

template <typename iterator, typename object>
bool is_sorted(const iterator& begin, const iterator& end, bool(& func)(object, object)) {
	iterator prev = begin;
	for (auto it = std::next(begin); it != end; it = std::next(it)) {
		if (!func(*prev, *it))
			return false;
		prev = it;
	}
	return true;
}

template <typename iterator, typename object>
bool is_palindrome(const iterator& begin, const iterator& end, bool(& func)(object)) {
	for (auto itLeft = begin, itRight = std::prev(end); itLeft != end, itRight != begin; itLeft = std::next(itLeft), itRight = std::prev(itRight))
		if (func(*itLeft) ^ func(*itRight))
			return false;
	return true;
}