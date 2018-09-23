#include "stdafx.h"
#include "CppUnitTest.h"

#include "../BoyerMoore/chunk_multi_search.h"

#include <boost/algorithm/searching/boyer_moore_horspool.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace chunk_search_unit_tests
{
	TEST_CLASS(ChunkMultiSearch)
	{
	public:
		TEST_METHOD(ReturnsMatchLengthWhenOnePatternIsIdenticalToHaystack)
		{

			chunk_multi_search< std::string::const_iterator, boost::algorithm::boyer_moore_horspool> cms;
			std::string needle1{ "abc" }; 
			cms.add_needle(needle1.begin(), needle1.end());
			std::string needle2{ "bcd" };
			cms.add_needle(needle2.begin(), needle2.end());

			std::string haystack{ "abc" };
			auto found = cms(haystack.cbegin(), haystack.cend());

			Assert::IsTrue(haystack.cbegin() == found.first);
			Assert::IsTrue(haystack.cend() == found.last);
		}

		TEST_METHOD(ReturnsMatchLength0WhenNoneOfPatternsIsFoundInHaystack)
		{
			chunk_multi_search< std::string::const_iterator, boost::algorithm::boyer_moore_horspool> cms;
			std::string needle1{ "abc" };
			cms.add_needle(needle1.begin(), needle1.end());
			std::string needle2{ "bcd" };
			cms.add_needle(needle2.begin(), needle2.end());
			std::string needle3{ "cde" };
			cms.add_needle(needle3.begin(), needle3.end());

			std::string haystack{ "cbc" };
			auto found = cms(haystack.cbegin(), haystack.cend());

			Assert::IsTrue(haystack.cend() == found.first);
			Assert::IsTrue(haystack.cend() == found.last);
			Assert::IsTrue(haystack.cbegin() == found.partial_match_start);
		}

		TEST_METHOD(ReturnsMatchLengthWhenOneOfPatternsIsPartOfHaystack)
		{
			chunk_multi_search< std::string::const_iterator, boost::algorithm::boyer_moore_horspool> cms;
			std::string needle1{ "abc" };
			cms.add_needle(needle1.begin(), needle1.end());
			std::string needle2{ "bcd" };
			cms.add_needle(needle2.begin(), needle2.end());
			std::string needle3{ "cde" };
			cms.add_needle(needle3.begin(), needle3.end());

			std::string haystack{ "bcabcde" };
			auto found = cms(haystack.cbegin(), haystack.cend());

			Assert::AreEqual('a', *found.first);
			Assert::AreEqual('d', *found.last);
		}

		TEST_METHOD(ReturnsMatchLengthOfFoundWhenOneOfPatternsIsPartOfHaystack)
		{
			chunk_multi_search< std::string::const_iterator, boost::algorithm::boyer_moore_horspool> cms;
			std::string needle1{ "abc" };
			cms.add_needle(needle1.begin(), needle1.end());
			std::string needle2{ "bcag" };
			cms.add_needle(needle2.begin(), needle2.end());
			std::string needle3{ "bcde" };
			cms.add_needle(needle3.begin(), needle3.end());
			std::string needle4{ "cac" };
			cms.add_needle(needle4.begin(), needle4.end());

			std::string haystack{ "bcabcde" };
			auto found = cms(haystack.cbegin(), haystack.cend());

			Assert::AreEqual('a', *found.first);
			Assert::AreEqual('d', *found.last);
		}

		TEST_METHOD(ReturnsMatchLengthOfFirstPatternMatchedEntirelyWhenAllPatternsArePartOfHaystack)
		{
			chunk_multi_search< std::string::const_iterator, boost::algorithm::boyer_moore_horspool> cms;
			std::string needle1{ "abcde" };
			cms.add_needle(needle1.begin(), needle1.end());
			std::string needle2{ "abcd" };
			cms.add_needle(needle2.begin(), needle2.end());
			std::string needle3{ "bcd" };
			cms.add_needle(needle3.begin(), needle3.end());
			std::string needle4{ "bcde" };
			cms.add_needle(needle4.begin(), needle4.end());

			std::string haystack{ "aaabcdef" };
			auto found = cms(haystack.cbegin(), haystack.cend());

			Assert::AreEqual('a', *found.first);
			Assert::AreEqual('e', *found.last);
		}

		TEST_METHOD(ReturnsMatchLengthOfLongestPatternForPatternsThatHaveSameEnd)
		{
			chunk_multi_search< std::string::const_iterator, boost::algorithm::boyer_moore_horspool> cms;
			std::string needle1{ "aaabcd" };
			cms.add_needle(needle1.begin(), needle1.end());
			std::string needle2{ "aabcd" };
			cms.add_needle(needle2.begin(), needle2.end());
			std::string needle3{ "abcd" };
			cms.add_needle(needle3.begin(), needle3.end());

			std::string haystack{ "aaaabcdef" };
			auto found = cms(haystack.cbegin(), haystack.cend());

			Assert::AreEqual('a', *found.first);
			Assert::AreEqual('e', *found.last);
			Assert::AreEqual(long(6), long(std::distance(found.first, found.last)));
		}

		TEST_METHOD(ReturnsMatchLengthWhenTheOnlyPatternIsIdenticalToHaystack)
		{
			chunk_multi_search< std::string::const_iterator, boost::algorithm::boyer_moore_horspool> cms;
			std::string needle1{ "abc" };
			cms.add_needle(needle1.begin(), needle1.end());

			std::string haystack{ "abc" };
			auto found = cms(haystack.cbegin(), haystack.cend());

			Assert::IsTrue(haystack.cbegin() == found.first);
			Assert::IsTrue(haystack.cend() == found.last);
		}

		TEST_METHOD(ReturnsMatchLength0WhenTheOnlyPatternsIsFoundInHaystack)
		{
			chunk_multi_search< std::string::const_iterator, boost::algorithm::boyer_moore_horspool> cms;
			std::string needle1{ "abc" };
			cms.add_needle(needle1.begin(), needle1.end());

			std::string haystack{ "cbc" };
			auto found = cms(haystack.cbegin(), haystack.cend());

			Assert::IsTrue(haystack.cend() == found.first);
			Assert::IsTrue(haystack.cend() == found.last);
		}

		//TEST_METHOD(ReturnsResultWhenPatternsAreProvidedAsCollectionToConstructor)
		//{
		//	std::string patterns[] = { "abc", "bcd" };
		//	composite_chunk_search<std::string> cs(patterns);

		//	std::string haystack{ " abcd" };
		//	auto found = cs.search(haystack.cbegin(), haystack.cend());

		//	Assert::AreEqual(size_t(3), found.match_length);
		//	Assert::AreEqual(long(4), long(std::distance(haystack.cbegin(), found.end)));
		//}

		//TEST_METHOD(ReturnsResultWhenPatternIsAddedSubsequently)
		//{
		//	composite_chunk_search<std::string> ccs({ "bcd" });

		//	std::string haystack1{ " abce" };
		//	auto found = ccs.search(haystack1.cbegin(), haystack1.cend());

		//	Assert::AreEqual(size_t(0), found.match_length);

		//	ccs.add_pattern("abcd");

		//	std::string haystack2{ "dabcda" };
		//	found = ccs.search(haystack2.cbegin(), haystack2.cend());

		//	Assert::AreEqual(size_t(4), found.match_length);
		//	Assert::AreEqual(long(5), long(std::distance(haystack2.cbegin(), found.end)));
		//}
	};
}
