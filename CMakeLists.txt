#-------------------------------------------------------------------------------
# PBCPP CMAKE
#-------------------------------------------------------------------------------
project(pbcpp CXX)
cmake_minimum_required(VERSION 2.8.5)

#-------------------------------------------------------------------------------
# GUARD AGAINST IN SOURCE BUILDS
#-------------------------------------------------------------------------------
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt. ")
endif()

#-------------------------------------------------------------------------------
# SET BUILD TYPE TO RELEASE IF NONE PROVIDED
#-------------------------------------------------------------------------------
if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

#-------------------------------------------------------------------------------
# CMAKE INCLUDES
#-------------------------------------------------------------------------------
include(GNUInstallDirs)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

#-------------------------------------------------------------------------------
# PARSE VERSION NUMBER
#-------------------------------------------------------------------------------
file(READ "${PROJECT_SOURCE_DIR}/src/pbcpp/src/Core/Version.hpp" _pbcpp_version_header)
string(REGEX MATCH "define[ \t]+PBCPP_MAJOR_VERSION[ \t]+([0-9]+)" _pbcpp_major_version_match "${_pbcpp_version_header}")
set(PBCPP_MAJOR_VERSION "${CMAKE_MATCH_1}")
string(REGEX MATCH "define[ \t]+PBCPP_MINOR_VERSION[ \t]+([0-9]+)" _pbcpp_minor_version_match "${_pbcpp_version_header}")
set(PBCPP_MINOR_VERSION "${CMAKE_MATCH_1}")
string(REGEX MATCH "define[ \t]+PBCPP_PATCH_VERSION[ \t]+([0-9]+)" _pbcpp_patch_version_match "${_pbcpp_version_header}")
set(PBCPP_PATCH_VERSION "${CMAKE_MATCH_1}")
set(PBCPP_VERSION_NUMBER ${PBCPP_MAJOR_VERSION}.${PBCPP_MINOR_VERSION}.${PBCPP_PATCH_VERSION})

#-------------------------------------------------------------------------------
# SUBDIRECTORIES
#-------------------------------------------------------------------------------
add_subdirectory(test)
add_subdirectory(src)

#-------------------------------------------------------------------------------
# PKGCONFIG
#-------------------------------------------------------------------------------
if(NOT WIN32)
  option(PBCPP_BUILD_PKGCONFIG "Build the pkgconfig file." ON)
endif(NOT WIN32)
set(PKGCONFIG_INSTALL_DIR
  "${CMAKE_INSTALL_DATADIR}/pkgconfig"
  CACHE PATH "The directory relative to CMAKE_PREFIX_PATH where eigen3.pc is installed")
if(PBCPP_BUILD_PKGCONFIG)
  configure_file(pbcpp.pc.in pbcpp.pc @ONLY)
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/pbcpp.pc
    DESTINATION ${PKGCONFIG_INSTALL_DIR})
endif(PBCPP_BUILD_PKGCONFIG)

#-------------------------------------------------------------------------------
# INSTALLATION
#-------------------------------------------------------------------------------
set(INCLUDE_INSTALL_DIR "${CMAKE_INSTALL_INCLUDEDIR}/pbcpp"
  CACHE
    PATH "The directory relative to CMAKE_PREFIX_PATH where pbcpp header files are installed")

install(
  FILES signature_of_pbcpp
  DESTINATION ${INCLUDE_INSTALL_DIR} COMPONENT Devel)

# show version
message(STATUS "-----------------------------------------------------------------------------")
message(STATUS "pbcpp v${PBCPP_VERSION_NUMBER}")
message(STATUS "--------------+--------------------------------------------------------------")
message(STATUS "prefix        | ${CMAKE_PREFIX_PATH}")
message(STATUS "include dir   | ${CMAKE_PREFIX_PATH}/${CMAKE_INSTALL_INCLUDEDIR}")
message(STATUS "install dir   | ${CMAKE_PREFIX_PATH}/${INCLUDE_INSTALL_DIR}")
message(STATUS "--------------+--------------------------------------------------------------")
