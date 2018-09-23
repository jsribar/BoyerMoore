#pragma once

#include <algorithm>

template <typename NeedleIterator>
class simple_search
{
public:
	simple_search(NeedleIterator first, NeedleIterator last)
		: needle_first_m(first)
		, needle_last_m(last)
	{
	}

	template <typename HaystackIterator>
	std::pair<HaystackIterator, HaystackIterator> operator()(HaystackIterator first, HaystackIterator last)
	{
		auto found = std::search(first, last, needle_first_m, needle_last_m);
		if (found == last)
			return std::make_pair(last, last);
		auto found_end = found;
		std::advance(found_end, std::distance(needle_first_m, needle_last_m));
		return std::make_pair(found, found_end);
	}

private:
	NeedleIterator needle_first_m;
	NeedleIterator needle_last_m;
};
