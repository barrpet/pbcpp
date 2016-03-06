#include "catch.hpp"

#include <pbcpp/Math>

TEST_CASE("math constants", "[math][constants]")
{
  using pbcpp::Math::Constants;
  REQUIRE( Constants<double>::pi  == Approx( 3.1415926535 ).epsilon( 0.00001 ) );
  REQUIRE( Constants<float>::pi  == Approx( 3.1415926535 ).epsilon( 0.00001 ) );
  REQUIRE( Constants<>::pi  == Approx( 3.1415926535 ).epsilon( 0.00001 ) );
}
