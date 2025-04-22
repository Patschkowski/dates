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
/// @brief Module interface for DATE conversions.

module;

// C++ Standard Library
#include <ctime>
#include <chrono>

// Export definitions
#include "libdates_export.h"

export module dates;

/// @module dates
/// @brief Provides subroutines to convert to and from Microsoft's @c VARIANT
/// time format (@c VT_DATE) which is represented as a double.

export namespace dates {

/// @brief Convert from std::time_t to DATE.
/// @param time Time since epoch.
/// @return Variant time (DATE).
LIBDATES_EXPORT auto to_variant_time(std::time_t time) -> double;

/// @brief Convert from DATE to a time_point.
/// @param vtime Variant time (DATE).
/// @return time point.
LIBDATES_EXPORT auto from_variant_time(double vtime)
  -> std::chrono::system_clock::time_point;

}
