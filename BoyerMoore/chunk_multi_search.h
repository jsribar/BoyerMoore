#pragma once

#include "chunk_search.h"

#include <vector>

template <typename NeedleIterator, template <typename T = NeedleIterator, typename... Args> class Searcher>
class chunk_multi_search
{
public:
	void add_needle(NeedleIterator first, NeedleIterator last)
	{
		searchers_m.emplace_back(first, last);
	}

	template <typename HaystackIterator>
	chunk_search_result<HaystackIterator> operator()(HaystackIterator first, HaystackIterator last)
	{
		std::vector<chunk_search_result<HaystackIterator>> successful;
		HaystackIterator foremost = last;
		for (auto& search : searchers_m)
		{
			auto result = search(first, last);
			if (result.first != result.last)
				successful.push_back(result);
			else
				foremost = (std::min)(result.partial_match_start, foremost);
		}
		if (successful.empty())
			return chunk_search_result<HaystackIterator>(last, last, foremost);
		// return match that ends foremost and if two end at the same position, return the shorter one
		return *std::min_element(successful.begin(), successful.end(), [](const auto& res1, const auto& res2)
		{
			return res1.first == res2.first ? res1.last < res2.last : res1.first < res2.first;
		});
	}
private:
	std::vector<chunk_search<NeedleIterator, Searcher>> searchers_m;
};
