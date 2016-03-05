project(pbcpp CXX)
cmake_minimum_required(VERSION 2.8.5)

include_directories(../)

file(GLOB PBCPP_TEST_SOURCES "*.cpp")

add_executable(unit_tests "${PBCPP_TEST_SOURCES}")

set_target_properties(unit_tests
  PROPERTIES
    CXX_STANDARD 11
    EXCLUDE_FROM_ALL 1
    EXCLUDE_FROM_DEFAULT_BUILD 1)

add_custom_target(check
  COMMAND unit_tests
  DEPENDS unit_tests)
  
