/// @file
/// @brief DATE conversion unit tests.

// C++ Standard Library
#include <chrono>

// Boost
#define BOOST_TEST_MODULE Dates Tests
#include <boost/test/unit_test.hpp>

import dates;

BOOST_AUTO_TEST_SUITE(dates_tests)

BOOST_AUTO_TEST_CASE(to_from_variant_time_is_symmetric)
{
  const auto expected{std::chrono::system_clock::now()};
  const auto uut{dates::from_variant_time(
    dates::to_variant_time(std::chrono::system_clock::to_time_t(expected)))};

  // Variant time resolves to seconds.
  BOOST_TEST(expected - uut < std::chrono::seconds{1});
}

BOOST_AUTO_TEST_SUITE_END()
