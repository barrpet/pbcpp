project(pbcpp CXX)
cmake_minimum_required(VERSION 2.8.5)

# guard against in-source builds
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt. ")
endif()

# guard against bad build-type strings
if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

# automatically parse the version number
file(READ "${PROJECT_SOURCE_DIR}/pbcpp/src/core/version.hpp" _pbcpp_version_header)
string(REGEX MATCH "define[ \t]+PBCPP_MAJOR_VERSION[ \t]+([0-9]+)" _pbcpp_major_version_match "${_pbcpp_version_header}")
set(PBCPP_MAJOR_VERSION "${CMAKE_MATCH_1}")
string(REGEX MATCH "define[ \t]+PBCPP_MINOR_VERSION[ \t]+([0-9]+)" _pbcpp_minor_version_match "${_pbcpp_version_header}")
set(PBCPP_MINOR_VERSION "${CMAKE_MATCH_1}")
string(REGEX MATCH "define[ \t]+PBCPP_PATCH_VERSION[ \t]+([0-9]+)" _pbcpp_patch_version_match "${_pbcpp_version_header}")
set(PBCPP_PATCH_VERSION "${CMAKE_MATCH_1}")
set(PBCPP_VERSION_NUMBER ${PBCPP_MAJOR_VERSION}.${PBCPP_MINOR_VERSION}.${PBCPP_PATCH_VERSION})

message(STATUS "pbcpp v${PBCPP_VERSION_NUMBER}")

add_subdirectory(pbcpp)
add_subdirectory(test)

