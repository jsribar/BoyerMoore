#include "StopWatch.h"
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <string>
#include <boost/algorithm/searching/boyer_moore.hpp>
#include <boost/algorithm/searching/boyer_moore_horspool.hpp>
#include <boost/algorithm/searching/knuth_morris_pratt.hpp>
#include <boost/utility/string_view.hpp>


constexpr int count = 1000000;

int main()
{
	std::ifstream is("input.txt", std::ios_base::in | std::ios_base::binary);
	if (!is)
		return 1;

	// get length of file:
	is.seekg(0, is.end);
	auto length = is.tellg();
	is.seekg(0, is.beg);

	std::string haystack;
	haystack.resize(length);
	is.read(&haystack[0], length);

    std::string needles[]{ "-----BEGIN ", "-----END " };
    std::string end{ "-----" };

    //for (const auto& needle : needles)
    //{
    //    std::cout << needle << std::endl;

    //    size_t total = 0;

    //    boost::algorithm::boyer_moore<std::string::const_iterator> bm(std::cbegin(needle), std::end(needle));
    //    std::cout << "Boyer-Moore" << std::endl;
    //    {
    //        StopWatch sw;
    //        for (int i = 0; i < count; ++i)
    //        {
    //            auto found = std::search(haystack.cbegin(), haystack.cend(), bm);
    //            total++;
    //        }
    //    }

    //    {
    //        StopWatch sw;
    //        for (int i = 0; i < count; ++i)
    //        {
    //            auto found = bm(haystack.cbegin(), haystack.cend());
    //            total++;
    //        }
    //    }

    //    boost::algorithm::boyer_moore_horspool<std::string::const_iterator> bmh(std::cbegin(needle), std::end(needle));
    //    std::cout << "Boyer-Moore-Horspool" << std::endl;
    //    {
    //        StopWatch sw;
    //        for (int i = 0; i < count; ++i)
    //        {
    //            auto found = std::search(haystack.cbegin(), haystack.cend(), bmh);
    //            total++;
    //        }
    //    }

    //    {
    //        StopWatch sw;
    //        for (int i = 0; i < count; ++i)
    //        {
    //            auto found = bmh(haystack.cbegin(), haystack.cend());
    //            total++;
    //        }
    //    }

    //    std::cout << "std::search" << std::endl;
    //    {
    //        StopWatch sw;
    //        for (int i = 0; i < count; ++i)
    //        {
    //            auto found = std::search(haystack.cbegin(), haystack.cend(), needle.cbegin(), needle.cend());
    //            total++;
    //        }
    //    }

    //    std::cout << "std::string.find - same string" << std::endl;
    //    total = 0;
    //    {
    //        StopWatch sw;
    //        for (int i = 0; i < count; ++i)
    //        {
    //            auto found = haystack.find(needle);
    //            total += found;
    //        }
    //    }

    //    std::cout << "std::string.find - new string each time" << std::endl;
    //    total = 0;
    //    {
    //        StopWatch sw;
    //        for (int i = 0; i < count; ++i)
    //        {
    //            std::string another(haystack.c_str());
    //            auto found = another.find(needle);
    //            total += found;
    //        }
    //    }
    //}

    std::cout << "REAL WORLD TEST" << std::endl;

    for (const auto& needle : needles)
    {
        std::cout << needle << std::endl;

        size_t total = 0;

        boost::algorithm::boyer_moore<std::string::const_iterator> bm_start(std::cbegin(needle), std::cend(needle));
        boost::algorithm::boyer_moore<std::string::const_iterator> bm_end(std::cbegin(end), std::cend(end));
        std::cout << "Boyer-Moore" << std::endl;
        {
            StopWatch sw;
            for (int i = 0; i < count; ++i)
            {
                auto found = std::search(haystack.cbegin(), haystack.cend(), bm_start);
                found = std::search(found + needle.size(), haystack.cend(), bm_end);
                total++;
            }
        }

        boost::algorithm::boyer_moore_horspool<std::string::const_iterator> bmh_start(std::cbegin(needle), std::cend(needle));
        boost::algorithm::boyer_moore_horspool<std::string::const_iterator> bmh_end(std::cbegin(end), std::cend(end));
        std::cout << "Boyer-Moore-Horspool" << std::endl;
        {
            StopWatch sw;
            for (int i = 0; i < count; ++i)
            {
                auto found = std::search(haystack.cbegin(), haystack.cend(), bmh_start);
                found = std::search(found + needle.size(), haystack.cend(), bmh_end);
                total++;
            }
        }

        std::cout << "std::search" << std::endl;
        {
            StopWatch sw;
            for (int i = 0; i < count; ++i)
            {
                auto found = std::search(haystack.cbegin(), haystack.cend(), needle.cbegin(), needle.cend());
                found = std::search(found + needle.size(), haystack.cend(), end.cbegin(), end.cend());
                total++;
            }
        }

    }
    return 0;
}

