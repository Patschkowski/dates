cmake_minimum_required(VERSION 3.30)

project(dates VERSION 0.1.0)

option(BUILD_DOC "build documentation" OFF)

set(CMAKE_CXX_EXTENSIONS FALSE)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN TRUE)

include(CTest)
include(GenerateExportHeader)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers) 

find_package(wil CONFIG REQUIRED)
find_package(cppwinrt CONFIG REQUIRED)
find_package(Microsoft.GSL CONFIG REQUIRED)
if(BUILD_TESTING)
  find_package(Boost REQUIRED COMPONENTS unit_test_framework)
endif()
if(BUILD_DOC)
  find_package(Doxygen)
endif()

set(dates_INSTALL_CMAKEDIR
  ${CMAKE_INSTALL_LIBDIR}/cmake/dates
  CACHE STRING "Path to dates cmake files")

add_library(libdates)
generate_export_header(libdates)
target_sources(libdates
  PUBLIC FILE_SET HEADERS BASE_DIRS ${CMAKE_CURRENT_BINARY_DIR} FILES
    "${CMAKE_CURRENT_BINARY_DIR}/libdates_export.h"
  PUBLIC FILE_SET CXX_MODULES FILES
    "libdates/dates.cppm"
  PRIVATE
    "libdates/dates.cpp")
target_compile_features(libdates
  PUBLIC
    cxx_std_20)
target_link_libraries(libdates
  PUBLIC
    Microsoft.GSL::GSL
    WIL::WIL
    Microsoft::CppWinRT)

if(BUILD_TESTING)
  add_executable(libdates_tests)
  target_sources(libdates_tests
    PRIVATE
      "libdates/dates.test.cpp")
  target_link_libraries(libdates_tests
    PRIVATE
      Boost::unit_test_framework
      libdates)

  add_test(libtest_dates_to_from_variant_time_is_symmetric
    libdates_tests -t "libdates_tests/to_from_variant_time_is_symmetric")
endif()

if(BUILD_DOC AND DOXYGEN_FOUND)
  set(DOXYGEN_EXCLUDE_PATTERNS */.vs/* */out/*)
  doxygen_add_docs(doxygen ${CMAKE_CURRENT_SOURCE_DIR} ALL)
endif()

configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/datesConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/datesConfig.cmake
  INSTALL_DESTINATION ${dates_INSTALL_CMAKEDIR}
)

write_basic_package_version_file( 
  datesConfigVersion.cmake
  COMPATIBILITY SameMajorVersion 
)

install(TARGETS libdates
  EXPORT datesTargets
  RUNTIME
    DESTINATION ${CMAKE_INSTALL_BINDIR}
    COMPONENT dates_RunTime
  LIBRARY
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
    COMPONENT dates_RunTime
    NAMELINK_COMPONENT dates_Development
  ARCHIVE
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
    COMPONENT dates_Development
  FILE_SET HEADERS
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  FILE_SET CXX_MODULES
    DESTINATION ${dates_INSTALL_CMAKEDIR}/src
  INCLUDES
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT datesTargets
  FILE datesTargets.cmake
  DESTINATION ${dates_INSTALL_CMAKEDIR}
  NAMESPACE dates::
  CXX_MODULES_DIRECTORY .)
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/datesConfig.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/datesConfigVersion.cmake
  DESTINATION ${dates_INSTALL_CMAKEDIR})
