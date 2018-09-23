// BoyerMoore.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "StopWatch.h"
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <boost/algorithm/searching/boyer_moore.hpp>
#include <boost/algorithm/searching/boyer_moore_horspool.hpp>

#include "chunk_search.h"
#include "chunk_multi_search.h"


int main()
{
	std::string needle("-----END ");
	std::string haystack("abcd -----END ");

	chunk_search<std::string::const_iterator, boost::algorithm::boyer_moore_horspool> cs(needle.cbegin(), needle.cend());
	auto found = cs(haystack.begin(), haystack.end());

	std::string haystack2("abcd -----END");

	found = cs(haystack2.begin(), haystack2.end());

	return 0;
}

//int main()
//{
//	std::string needle1("-----END ");
//	std::string needle2("------END ");
//
//	chunk_multi_search<std::string::iterator, boost::algorithm::boyer_moore_horspool> cms;
//	cms.add_needle(needle1.begin(), needle1.end());
//	cms.add_needle(needle2.begin(), needle2.end());
//
//	std::string haystack("abcd ------END ");
//	auto found = cms(haystack.begin(), haystack.end());
//
//	haystack = ("abcd -----END ");
//	found = cms(haystack.begin(), haystack.end());
//
//	haystack = ("abcd -----EN");
//	found = cms(haystack.begin(), haystack.end());
//
//	haystack = ("abcd ------EN");
//	found = cms(haystack.begin(), haystack.end());
//
//	haystack = ("abcdefghijklmno");
//	found = cms(haystack.begin(), haystack.end());
//
//	return 0;
//}

//constexpr int count = 1000000;
//
//int main()
//{
//	std::ifstream is("input.txt", std::ios_base::in | std::ios_base::binary);
//	if (!is)
//		return 1;
//
//	// get length of file:
//	is.seekg(0, is.end);
//	auto length = is.tellg();
//	is.seekg(0, is.beg);
//
//	std::string haystack;
//	haystack.resize(length);
//	is.read(&haystack[0], length);
//
//
//	//std::string needle("-----BEGIN CERTIFICATE-----");
//	std::string needle("-----END ");
//	long total = 0;
//
//	boost::algorithm::boyer_moore<std::string::const_iterator> bm(std::cbegin(needle), std::end(needle));
//
//	{
//		StopWatch sw;
//		for (int i = 0; i < count; ++i)
//		{
//			auto found = bm(haystack.cbegin(), haystack.cend());
//			total++;
//		}
//	}
//
//	boost::algorithm::boyer_moore_horspool<std::string::const_iterator> bmh(std::cbegin(needle), std::end(needle));
//
//	{
//		StopWatch sw;
//		for (int i = 0; i < count; ++i)
//		{
//			auto found = bmh(haystack.cbegin(), haystack.cend());
//			total++;
//		}
//	}
//
//	{
//		StopWatch sw;
//		for (int i = 0; i < count; ++i)
//		{
//			auto found = std::search(haystack.cbegin(), haystack.cend(), needle.cbegin(), needle.cend());
//			total++;
//		}
//	}
//
//	{
//		StopWatch sw;
//		for (int i = 0; i < count; ++i)
//		{
//			auto found = haystack.find(needle);
//			total++;
//		}
//	}
//
//	{
//		StopWatch sw;
//		for (int i = 0; i < count; ++i)
//		{
//			std::string another(haystack.c_str());
//			auto found = another.find(needle);
//			total++;
//		}
//	}
//
//	return 0;
//}
//
