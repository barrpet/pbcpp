#define CATCH_CONFIG_MAIN
#include "catch.hpp"

template <typename T = unsigned long long>
T factorial(const T& n)
{
  if(n == 0 | n == 1) { return 1; }
  else if(n < 0) { throw; }
  else { return n * factorial(n-1); }
}

TEST_CASE("factorial", "[factorial]")
{
  REQUIRE( factorial(4) == 24 );
}
