#pragma once

template <typename iterator, typename object>
bool all_of(const iterator& begin, const iterator& end, bool (&func)(object));

template <typename iterator, typename object>
bool is_sorted(const iterator& begin, const iterator& end, bool (&func)(object, object));

template <typename iterator, typename object>
bool is_palindrome(const iterator& begin, const iterator& end, bool (&func)(object));

#include "Iterator.cpp"