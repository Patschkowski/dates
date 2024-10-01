cmake_minimum_required(VERSION 3.28)

project(DATES)

find_package(wil CONFIG REQUIRED)
find_package(cppwinrt CONFIG REQUIRED)
find_package(Boost COMPONENTS unit_test_framework)
find_package(Doxygen)

add_library(dates STATIC)
target_sources(dates PRIVATE "src/dates.cpp")
target_sources(dates PUBLIC FILE_SET CXX_MODULES FILES "src/dates.cppm")
target_link_libraries(dates PUBLIC WIL::WIL Microsoft::CppWinRT)

if(${Boost_unit_test_framework_FOUND})
  add_executable(dates_tests)
  target_sources(dates_tests PRIVATE "tests/dates_tests.cpp")
  target_link_libraries(dates_tests PRIVATE Boost::unit_test_framework dates)

  include(CTest)
  enable_testing()
  add_test(test_dates_to_from_variant_time_is_symmetric dates_tests -t "dates_tests/to_from_variant_time_is_symmetric")
endif()

if(${DOXYGEN_FOUND})
  set(DOXYGEN_EXCLUDE_PATTERNS */out/* */.vs/*)
  doxygen_add_docs(doxygen ${CMAKE_CURRENT_SOURCE_DIR} ALL)
endif()