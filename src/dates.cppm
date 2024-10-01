/// @file
/// @brief Module interface for DATE conversions.

module;

// C++ Standard Library
#include <ctime>
#include <chrono>

export module dates;

/// @module dates
/// @brief Provides subroutines to convert to and from Microsoft's @c VARIANT
/// time format (@c VT_DATE) which is represented as a double.

export namespace dates {

/// @brief Convert from std::time_t to DATE.
/// @param time Time since epoch.
/// @return Variant time (DATE).
double to_variant_time(std::time_t time);

/// @brief Convert from DATE to a time_point.
/// @param vtime Variant time (DATE).
/// @return time point.
std::chrono::system_clock::time_point from_variant_time(double vtime);

}
