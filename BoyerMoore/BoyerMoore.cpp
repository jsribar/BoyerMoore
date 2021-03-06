#include "StopWatch.h"
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <string>
#include <boost/algorithm/searching/boyer_moore.hpp>
#include <boost/algorithm/searching/boyer_moore_horspool.hpp>

#ifdef _DEBUG
constexpr size_t count = 100;
#else
constexpr size_t count = 1000000;
#endif

int main()
{
	const std::string filenames[] { "input.txt", "sinput.txt" };

	std::string needles[]{ "-----BEGIN ", "-----END " };
	std::string end{ "-----" };

	size_t total = 0;

	for (const auto& filename : filenames)
	{
		std::ifstream is(filename, std::ios_base::in | std::ios_base::binary);
		if (!is)
			return 1;

		// get length of file:
		is.seekg(0, is.end);
		auto length = is.tellg();
		is.seekg(0, is.beg);

		std::cout << std::endl << "Search string length: " << length << std::endl;

		std::string haystack;
		haystack.resize(length);
		is.read(&haystack[0], length);

		for (const auto& needle : needles)
		{
			std::cout << std::endl << "Searching for " << needle << std::endl;

			boost::algorithm::boyer_moore<std::string::const_iterator> bm_start(std::cbegin(needle), std::cend(needle));
			boost::algorithm::boyer_moore<std::string::const_iterator> bm_end(std::cbegin(end), std::cend(end));
			std::cout << "Boyer-Moore:" << std::endl;
			{
				StopWatch sw;
				for (size_t i = 0; i < count; ++i)
				{
					auto found = std::search(haystack.cbegin(), haystack.cend(), bm_start);
					assert(found != haystack.cend());
					found = std::search(found + needle.size(), haystack.cend(), bm_end);
					assert(found != haystack.cend());
					total++;
				}
			}

			boost::algorithm::boyer_moore_horspool<std::string::const_iterator> bmh_start(std::cbegin(needle), std::cend(needle));
			boost::algorithm::boyer_moore_horspool<std::string::const_iterator> bmh_end(std::cbegin(end), std::cend(end));
			std::cout << "Boyer-Moore-Horspool:" << std::endl;
			{
				StopWatch sw;
				for (size_t i = 0; i < count; ++i)
				{
					auto found = std::search(haystack.cbegin(), haystack.cend(), bmh_start);
					assert(found != haystack.cend());
					found = std::search(found + needle.size(), haystack.cend(), bmh_end);
					assert(found != haystack.cend());
					total++;
				}
			}

			std::cout << "std::search:" << std::endl;
			{
				StopWatch sw;
				for (size_t i = 0; i < count; ++i)
				{
					auto found = std::search(haystack.cbegin(), haystack.cend(), needle.cbegin(), needle.cend());
					assert(found != haystack.cend());
					found = std::search(found + needle.size(), haystack.cend(), end.cbegin(), end.cend());
					assert(found != haystack.cend());
					total++;
				}
			}
		}

		std::cout << std::endl << "Reinitialized on each search: " << std::endl;

		for (const auto& needle : needles)
		{
			std::cout << std::endl << "Searching for " << needle << std::endl;

			size_t total = 0;

			std::cout << "Boyer-Moore:" << std::endl;
			{
				StopWatch sw;
				for (size_t i = 0; i < count; ++i)
				{
					boost::algorithm::boyer_moore<std::string::const_iterator> bm_start(std::cbegin(needle), std::cend(needle));
					auto found = std::search(haystack.cbegin(), haystack.cend(), bm_start);
					assert(found != haystack.cend());
					boost::algorithm::boyer_moore<std::string::const_iterator> bm_end(std::cbegin(end), std::cend(end));
					found = std::search(found + needle.size(), haystack.cend(), bm_end);
					assert(found != haystack.cend());
					total++;
				}
			}

			std::cout << "Boyer-Moore-Horspool:" << std::endl;
			{
				StopWatch sw;
				for (size_t i = 0; i < count; ++i)
				{
					boost::algorithm::boyer_moore_horspool<std::string::const_iterator> bmh_start(std::cbegin(needle), std::cend(needle));
					auto found = std::search(haystack.cbegin(), haystack.cend(), bmh_start);
					assert(found != haystack.cend());
					boost::algorithm::boyer_moore_horspool<std::string::const_iterator> bmh_end(std::cbegin(end), std::cend(end));
					found = std::search(found + needle.size(), haystack.cend(), bmh_end);
					assert(found != haystack.cend());
					total++;
				}
			}

			std::cout << "std::search:" << std::endl;
			{
				StopWatch sw;
				for (size_t i = 0; i < count; ++i)
				{
					auto found = std::search(haystack.cbegin(), haystack.cend(), needle.cbegin(), needle.cend());
					assert(found != haystack.cend());
					found = std::search(found + needle.size(), haystack.cend(), end.cbegin(), end.cend());
					assert(found != haystack.cend());
					total++;
				}
			}
		}
	}
	std::cout << std::endl << "Total searches: " << total << std::endl;

    return 0;
}

