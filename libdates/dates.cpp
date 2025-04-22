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
/// @brief Module implementation for DATE conversions.

module;

// C++ Standard Library
#include <chrono>
#include <ctime>

// Windows Implementation Library
#include <wil/cppwinrt.h>
#include <wil/result.h>

// Guideline Support Library
#include <gsl/assert>

module dates;

namespace dates {

auto to_variant_time(std::time_t time) -> double
{
  const FILETIME                  ft{static_cast<FILETIME>(
    winrt::clock::to_file_time(winrt::clock::from_time_t(time)))};
  GSL_SUPPRESS(type.5) SYSTEMTIME st;
  GSL_SUPPRESS(type.5) DOUBLE     vtime;

  THROW_LAST_ERROR_IF(!FileTimeToSystemTime(&ft, &st));
  THROW_IF_WIN32_BOOL_FALSE(SystemTimeToVariantTime(&st, &vtime));

  return vtime;
}

auto from_variant_time(double vtime) -> std::chrono::system_clock::time_point
{
  GSL_SUPPRESS(type.5) FILETIME   ft;
  GSL_SUPPRESS(type.5) SYSTEMTIME st;

  THROW_IF_WIN32_BOOL_FALSE(VariantTimeToSystemTime(vtime, &st));
  THROW_LAST_ERROR_IF(!SystemTimeToFileTime(&st, &ft));

  return std::chrono::clock_cast<std::chrono::system_clock>(
    winrt::clock::from_file_time(ft));
}

}
