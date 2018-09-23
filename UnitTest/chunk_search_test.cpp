#include "stdafx.h"
#include "CppUnitTest.h"

#include "../BoyerMoore/chunk_search.h"

#include <boost/algorithm/searching/boyer_moore_horspool.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace chunk_search_unit_tests
{
	TEST_CLASS(ChunkSearch)
	{
	public:
		TEST_METHOD(ReturnsMatchLengthEqualToPatternLenghtWhenPatternIsIdenticalToHaystack)
		{
			std::string needle{ "abc" };
			chunk_search<std::string::const_iterator, boost::algorithm::boyer_moore_horspool> cs(needle.cbegin(), needle.cend());

			std::string haystack{ "abc" };
			auto found = cs(haystack.cbegin(), haystack.cend());

			Assert::AreEqual('a', *found.first);
			Assert::IsTrue(haystack.cend() == found.last);
		}

		TEST_METHOD(ReturnsMatchLengthWhenPatternIsPartOfHaystack)
		{
			std::string needle{ "abc" };
			chunk_search<std::string::const_iterator, boost::algorithm::boyer_moore_horspool> cs(needle.cbegin(), needle.cend());

			std::string haystack{ "01abc23" };
			auto found = cs(haystack.cbegin(), haystack.cend());

			Assert::AreEqual('a', *found.first);
			Assert::AreEqual('2', *found.last);
		}

		TEST_METHOD(ReturnsMatchLengthWhenPatternIsPartOfHaystackPrecedeedWithPartialMatch)
		{
			std::string needle{ "abc" };
			chunk_search<std::string::const_iterator, boost::algorithm::boyer_moore_horspool> cs(needle.cbegin(), needle.cend());

			std::string haystack{ "ababc" };
			auto found = cs(haystack.cbegin(), haystack.cend());

			Assert::AreEqual('a', *found.first);
			Assert::IsTrue(haystack.cend() == found.last);
		}

		TEST_METHOD(ReturnsMatchLength0IfPatternIsNotFound)
		{
			std::string needle{ "abd" };
			chunk_search<std::string::const_iterator, boost::algorithm::boyer_moore_horspool> cs(needle.cbegin(), needle.cend());

			std::string haystack{ "abc" };
			auto found = cs(haystack.cbegin(), haystack.cend());

			Assert::IsTrue(found.first == found.last);
			Assert::IsTrue(haystack.cend() == found.first);
		}

		TEST_METHOD(ReturnsMatchLength0IfOnlyPartOfPatternIsFound)
		{
			std::string needle{ "012ab" };
			chunk_search<std::string::const_iterator, boost::algorithm::boyer_moore_horspool> cs(needle.cbegin(), needle.cend());

			std::string haystack{ "012" };
			auto found = cs(haystack.cbegin(), haystack.cend());

			Assert::IsTrue(haystack.cend() == found.last);
			Assert::AreEqual('0', *found.partial_match_start);
		}

		TEST_METHOD(ReturnsMatchLengthAfterSecondCallWhenPatternIsPartOfSecondHaystack)
		{
			std::string needle{ "abc" };
			chunk_search<std::string::const_iterator, boost::algorithm::boyer_moore_horspool> cs(needle.cbegin(), needle.cend());

			std::string haystack{ "0123" };
			auto found = cs(haystack.cbegin(), haystack.cend());

			Assert::IsTrue(haystack.cend() == found.last);
			Assert::IsTrue(haystack.cend() == found.first);

			haystack = "012abcd";
			found = cs(haystack.cbegin(), haystack.cend());

			Assert::AreEqual('a', *found.first);
			Assert::AreEqual('d', *found.last);
		}

		TEST_METHOD(ReturnsMatchLengthAfterSecondCallWhenPartOfPatternIsInFirstHaystackButPatternIsPartOfSecondHaystack)
		{
			std::string needle{ "abc" };
			chunk_search<std::string::const_iterator, boost::algorithm::boyer_moore_horspool> cs(needle.cbegin(), needle.cend());

			std::string haystack{ "ab" };
			auto found = cs(haystack.cbegin(), haystack.cend());

			Assert::IsTrue(haystack.cend() == found.first);
			Assert::IsTrue(haystack.cend() == found.last);
			Assert::AreEqual('a', *found.partial_match_start);

			haystack = "abcd";
			found = cs(haystack.cbegin(), haystack.cend());

			Assert::AreEqual('a', *found.first);
			Assert::AreEqual('d', *found.last);
		}

		TEST_METHOD(ReturnsMatchLengthAfterSecondCallWhenPatternIsSplitBetweenFirstAndSecondHaystacks)
		{
			std::string needle{ "abc" };
			chunk_search<std::string::const_iterator, boost::algorithm::boyer_moore_horspool> cs(needle.cbegin(), needle.cend());

			std::string haystack{ "a" };
			auto found = cs(haystack.cbegin(), haystack.cend());

			Assert::IsTrue(haystack.cend() == found.first);
			Assert::IsTrue(haystack.cend() == found.last);
			Assert::AreEqual('a', *found.partial_match_start);

			haystack = "bc";
			found = cs(haystack.cbegin(), haystack.cend());

			Assert::IsTrue(haystack.cend() == found.first);
			Assert::IsTrue(haystack.cend() == found.last);
		}

		TEST_METHOD(ReturnsMatchLengthAfterSecondCallWhenPartialPatternIsSplitBetweenFirstAndSecondHaystacksButIsInSecondHaystack)
		{
			std::string needle{ "abc" };
			chunk_search<std::string::const_iterator, boost::algorithm::boyer_moore_horspool> cs(needle.cbegin(), needle.cend());

			std::string haystack{ "a" };
			auto found = cs(haystack.cbegin(), haystack.cend());

			Assert::IsTrue(haystack.cend() == found.first);
			Assert::IsTrue(haystack.cend() == found.last);
			Assert::AreEqual('a', *found.partial_match_start);

			haystack = "bdabcd";
			found = cs(haystack.cbegin(), haystack.cend());

			Assert::AreEqual('a', *found.first);
			Assert::AreEqual('d', *found.last);
		}

		TEST_METHOD(ReturnsMatchLengthAfterSecondCallWhenPatternIsInSecondHaystack)
		{
			std::string needle{ "abc" };
			chunk_search<std::string::const_iterator, boost::algorithm::boyer_moore_horspool> cs(needle.cbegin(), needle.cend());

			std::string haystack{ "ab" };
			auto found = cs(haystack.cbegin(), haystack.cend());

			Assert::IsTrue(haystack.cend() == found.first);
			Assert::IsTrue(haystack.cend() == found.last);

			haystack = "abc";
			found = cs(haystack.cbegin(), haystack.cend());

			Assert::IsTrue(haystack.cbegin() == found.first);
			Assert::IsTrue(haystack.cend() == found.last);
		}

		TEST_METHOD(ReturnsIteratorToEndOfFoundAfterSecondCallWhenPatternIsInSecondHaystackButNoMatchInFirstHaystack)
		{
			std::string needle{ "abc" };
			chunk_search<std::string::const_iterator, boost::algorithm::boyer_moore_horspool> cs(needle.cbegin(), needle.cend());

			std::string haystack{ "def" };
			cs(haystack.cbegin(), haystack.cend());

			haystack = "abc";
			auto found = cs(haystack.cbegin(), haystack.cend());

			Assert::IsTrue(haystack.cbegin() == found.first);
			Assert::IsTrue(haystack.cend() == found.last);
		}

	};
}
