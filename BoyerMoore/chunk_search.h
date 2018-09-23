#pragma once

#include <cassert>
#include <iterator>

template <typename HaystackIterator>
struct chunk_search_result
{
	HaystackIterator first;
	HaystackIterator last;
	HaystackIterator partial_match_start;

	chunk_search_result(HaystackIterator first, HaystackIterator last, HaystackIterator partial_match_start)
		: first(first)
		, last(last)
		, partial_match_start(partial_match_start)
	{}
};


template <typename NeedleIterator, template <typename T = NeedleIterator, typename... Args> class Searcher>
class chunk_search
{
public:
	chunk_search(NeedleIterator first, NeedleIterator last)
		: searcher_m(first, last)
		, needle_first_m(first)
		, needle_last_m(last)
	{
	}

	template <typename HaystackIterator>
	chunk_search_result<HaystackIterator> operator()(HaystackIterator first, HaystackIterator last)
	{
		auto found = searcher_m(first, last);
		if (found.first != found.second)
			return chunk_search_result<HaystackIterator>(found.first, found.second, found.first);

		return chunk_search_result<HaystackIterator>(found.first, found.second, find_partial_match_start(first, last));
	}

private:
	Searcher<NeedleIterator> searcher_m;
	NeedleIterator needle_first_m;
	NeedleIterator needle_last_m;

	template <typename HaystackIterator>
	HaystackIterator find_partial_match_start(HaystackIterator first, HaystackIterator last)
	{
		HaystackIterator search_from = last;
		auto needle_length = std::distance(needle_first_m, needle_last_m);
		if (needle_length < std::distance(first, last))
			std::advance(search_from, -needle_length);
		else
			search_from = first;
		return std::find(search_from, last, *needle_first_m);
	}
};
