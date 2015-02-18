#include <iostream>
#include "pbmath.hpp"


void test_pbmath_gcd()
{
  //Should be 4
  unsigned t1 = pbmath::gcd(8, 12);
  std::cout << "Test 1: gcd(8, 12) = 4\n";
  std::cout << t1 << " == " << 4 << std::endl;
  
  //Should be 14
  unsigned t2 = pbmath::gcd(56, 42);
  std::cout << "Test 2: gcd(56, 42) = 14\n";
  std::cout << t2 << " == " << 14 << std::endl;
  
  //Should be 1
  unsigned t3 = pbmath::gcd(9, 28);
  std::cout << "Test 3: gcd(9, 28) = 1\n";
  std::cout << t3 << " == " << 1 << std::endl;
}

void test_is_prime_miller_rabin()
{
  unsigned t1 = 1;
  std::cout << "Test 1: is_prime_miller_rabin(1) = 0\n";
  std::cout << pbmath::is_prime_miller_rabin(t1);
  std::cout << " = 0\n";
  
  unsigned t2 = 2;
  std::cout << "Test 2: is_prime_miller_rabin(2) = 1\n";
  std::cout << pbmath::is_prime_miller_rabin(t2);
  std::cout << " = 1\n";
  
  unsigned t3 = 9;
  std::cout << "Test 3: is_prime_miller_rabin(9) = 0\n";
  std::cout << pbmath::is_prime_miller_rabin(t3);
  std::cout << " = 0\n";
  
  unsigned t4 = 31;
  std::cout << "Test 4: is_prime_miller_rabin(31) = 1\n";
  std::cout << pbmath::is_prime_miller_rabin(t4);
  std::cout << " = 1\n";
  
  unsigned t5 = 121;
  std::cout << "Test 5: is_prime_miller_rabin(121) = 0\n";
  std::cout << pbmath::is_prime_miller_rabin(t5);
  std::cout << " = 0\n";
}

int main(int argc, const char** argv)
{
  test_pbmath_gcd();
  std::cout << std::endl;
  test_is_prime_miller_rabin();
  return 0;
}
