#include "catch.hpp"

#include <pbcpp/Math>

TEST_CASE("math constants", "[math][constants]")
{
  using pbcpp::Math::Constants;
  REQUIRE( Constants<double>::pi  == Approx( 3.1415926535 ).epsilon( 0.00001 ) );
  REQUIRE( Constants<float>::pi  == Approx( 3.1415926535 ).epsilon( 0.00001 ) );
  REQUIRE( Constants<>::pi  == Approx( 3.1415926535 ).epsilon( 0.00001 ) );
}

TEST_CASE("math gcd", "[math][gcd]")
{
  using namespace pbcpp::Math;
  SECTION("standard")
  {
    REQUIRE( gcd(30, 12) == 6 );
    REQUIRE( gcd(13452, 864) == 12 );
    REQUIRE( gcd(543234, 432143) == gcd(432143, 543234) );
  }
  
  SECTION("zero, negatives, equal")
  {
    REQUIRE( gcd(14, 0) == 14 );
    REQUIRE( gcd(0, 111) == 111 );
    REQUIRE( gcd(756, 756) == 756 );
    REQUIRE( gcd(-3, 9) == 3);
    REQUIRE( gcd(9, -3) == 3 );
    REQUIRE( gcd(-543234, -432143) == gcd(432143, 543234) );
    REQUIRE( gcd(-543234, 432143) == gcd(432143, -543234) );
    REQUIRE( gcd(-543234, 432143) == gcd(-432143, 543234) );
  }
  
  SECTION("types")
  {
    int a = 30;
    unsigned b = 12;
    unsigned char ab = 6;
    short c = 110;
    unsigned long long d = 33;
    long long cd = 11;
    REQUIRE( gcd(a, b) == ab );
    REQUIRE( gcd(a, 0) == a );
    REQUIRE( gcd(0, a) == a );
    REQUIRE( gcd(c, d) == cd );
    REQUIRE( gcd(d, c) == cd );
    REQUIRE( gcd(0, c) == c );
    REQUIRE( gcd(c, 0) == c );
    REQUIRE( gcd(d, 0) == d );
  }
}

TEST_CASE("math isPrimeMillerRabin", "[math][isPrimeMillerRabin]")
{
  using namespace pbcpp::Math;
  REQUIRE( isPrimeMillerRabin(512927377) );
}
