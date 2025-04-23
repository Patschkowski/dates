cmake_minimum_required(VERSION 3.30)

project(libdates VERSION 0.1.0)

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

set(libdates_INSTALL_CMAKEDIR
  ${CMAKE_INSTALL_LIBDIR}/cmake/libdates
  CACHE STRING "Path to libdates cmake files")

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
target_compile_definitions(libdates
  PUBLIC
    _UNICODE
    UNICODE)
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
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/libdatesConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/libdatesConfig.cmake
  INSTALL_DESTINATION ${libdates_INSTALL_CMAKEDIR}
)

write_basic_package_version_file( 
  libdatesConfigVersion.cmake
  COMPATIBILITY SameMajorVersion 
)

install(TARGETS libdates
  EXPORT libdatesTargets
  RUNTIME
    DESTINATION ${CMAKE_INSTALL_BINDIR}
    COMPONENT libdates_RunTime
  LIBRARY
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
    COMPONENT libdates_RunTime
    NAMELINK_COMPONENT libdates_Development
  ARCHIVE
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
    COMPONENT libdates_Development
  FILE_SET HEADERS
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  FILE_SET CXX_MODULES
    DESTINATION ${libdates_INSTALL_CMAKEDIR}/src
  INCLUDES
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT libdatesTargets
  DESTINATION ${libdates_INSTALL_CMAKEDIR}
  CXX_MODULES_DIRECTORY .)
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/libdatesConfig.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/libdatesConfigVersion.cmake
  DESTINATION ${libdates_INSTALL_CMAKEDIR})