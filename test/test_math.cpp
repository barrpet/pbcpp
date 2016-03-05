#include "catch.hpp"

#include <pbcpp/math>

TEST_CASE("math constants", "[math][constants]")
{
  using pbcpp::math::constants;
  REQUIRE( constants<double>::pi  == Approx( 3.1415926535 ).epsilon( 0.00001 ) );
  REQUIRE( constants<float>::pi  == Approx( 3.1415926535 ).epsilon( 0.00001 ) );
  REQUIRE( constants<>::pi  == Approx( 3.1415926535 ).epsilon( 0.00001 ) );
}
