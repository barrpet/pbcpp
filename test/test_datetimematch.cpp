#include "catch.hpp"
#include <string>

#ifndef DEBUG
#define DEBUG
#define PBCPP_DEBUG 1
#else
#define PBCPP_DEBUG 0
#endif

#include <pbcpp/DateTimeMatch>

TEST_CASE("DateTimeMatch", "[datetime][datetimematch]")
{
  using std::string;
  using pbcpp::DateTimeMatch;
  DateTimeMatch dtm;
  
  SECTION("time")
  {
    string s0, s1, s2, s3;
    s0 = "23:12:03";
    s1 = "fsaljfa 000859 dfas";
    s2 = "12:45:59 453";
    REQUIRE( dtm.hasTime(s0) );
    REQUIRE( dtm.hasTime(s1) );
    REQUIRE( dtm.hasTime(s2) );
  }
  
  
}

#if (PBCPP_DEBUG == 1)
#undef DEBUG
#endif
