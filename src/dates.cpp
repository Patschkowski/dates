/// @file
/// @brief Module implementation for DATE conversions.

module;

// C++ Standard Library
#include <chrono>
#include <ctime>

// Windows Implementation Library
#include <wil/cppwinrt.h>
#include <wil/result.h>

module dates;

namespace dates {

double to_variant_time(std::time_t time)
{
  const FILETIME ft{static_cast<FILETIME>(
    winrt::clock::to_file_time(winrt::clock::from_time_t(time)))};
  SYSTEMTIME     st;
  DOUBLE         vtime;

  THROW_LAST_ERROR_IF(!FileTimeToSystemTime(&ft, &st));
  THROW_IF_WIN32_BOOL_FALSE(SystemTimeToVariantTime(&st, &vtime));

  return vtime;
}

std::chrono::system_clock::time_point from_variant_time(double vtime)
{
  FILETIME   ft;
  SYSTEMTIME st;

  THROW_IF_WIN32_BOOL_FALSE(VariantTimeToSystemTime(vtime, &st));
  THROW_LAST_ERROR_IF(!SystemTimeToFileTime(&st, &ft));

  return std::chrono::clock_cast<std::chrono::system_clock>(
    winrt::clock::from_file_time(ft));
}

}
