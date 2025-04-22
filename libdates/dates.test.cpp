// Convert to and from DATE data type used in VARIANTs.
// Copyright (C) 2025  Felix Patschkowski <felix.patschkowski@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

/// @file
/// @brief DATE conversion unit tests.

// C++ Standard Library
#include <chrono>

// Boost
#define BOOST_TEST_MODULE Dates Tests
#include <boost/test/unit_test.hpp>

import dates;

BOOST_AUTO_TEST_SUITE(libdates_tests)

BOOST_AUTO_TEST_CASE(to_from_variant_time_is_symmetric)
{
  const auto expected{std::chrono::system_clock::now()};
  const auto uut{dates::from_variant_time(
    dates::to_variant_time(std::chrono::system_clock::to_time_t(expected)))};

  // Variant time resolves to seconds.
  BOOST_TEST(expected - uut < std::chrono::seconds{1});
}

BOOST_AUTO_TEST_SUITE_END()
