#ifndef PBCPP_MATH_HPP
#define PBCPP_MATH_HPP

#include <type_traits>
#include <stdexcept>

/*!
 *  \addtogroup Math
 *  @{
 */
namespace pbcpp { namespace Math {

template <class T>
T unchecked_gcd(T u, T v)
{
  if(u < 0) { u *= -1; }
  if(v < 0) { v *= -1; }
  int shift;
  if(u == 0) { return v; }
  if(v == 0) { return u; }
  for(shift = 0; ((u | v) & 1) == 0; ++shift) {
    u >>= 1;
    v >>= 1;
  }
  while((u & 1) == 0)
    u >>= 1;
  do {
    while((v & 1) == 0)
      v >>= 1;
    if(u > v) {
      T t = v;
      v = u;
      u = t;
    }
    v = v - u;
  } while(v != 0);
  return u << shift;
}

/*! \fn int_type gcd(int_type u, int_type v)
 * \brief Return the greatest common divisor of two integers
 * \param u an integer (preferably unsigned)
 * \param v an integer (preferably unsigned)
 * \return \a gcd returns the greatest common divisor if two input integers
 */
template <typename _Ta = unsigned int,
          typename _Tb = _Ta,
          typename _Tr = typename std::common_type<_Ta, _Ta>::type>
_Tr gcd(const _Ta& u, const _Tb& v) {
  static_assert(std::is_integral<_Ta>::value, "gcd: arguments must be integral");
  static_assert(std::is_integral<_Tb>::value, "gcd: arguments must be integral");
  return unchecked_gcd(static_cast<_Tr>(u), static_cast<_Tr>(v));
}


template <class int_type, class ret_type = unsigned long long>
ret_type mul_mod(int_type a, int_type b, int_type mod)
{
  unsigned long long x = 0;
  unsigned long long y = a % mod;
  while(b > 0)
  {
    if((b & 1) == 1)
      x = (x + y) % mod;
    y = (y << 1) % mod;
    b >>= 1;
  }
  return (ret_type)(x % mod);
}

template <class int_type, class ret_type = unsigned long long>
ret_type mod_exp(int_type base, int_type exp, int_type mod)
{
  unsigned long long x = 1;
  unsigned long long y = (unsigned long long)(base);
  while(exp > 0) {
    if((exp & 1) == 1)
      x = (x * y) % mod;
    y = (y * y) % mod;
    exp >>= 1;
  }
  return (ret_type)(x % mod);
}

/*! \fn bool isPrimeMillerRabin(IntType n)
 * \brief Returns whether or not a number is probably prime
 * \param n The integer to test for primality
 * \param iters The number of iterations to run the test for
 * \return Technically returns either false or probably true
 */
template <class _T = unsigned int>
bool isPrimeMillerRabin(_T n, unsigned int iters = 25)
{
  if(n < 0) { throw std::runtime_error("isPrimeMillerRabin: argument must be greater than 0"); }
  if(n < 2) { return false; }
  if(n == 2) { return true; }
  if((n & 1) == 0) { return false; }
  
  _T s = n - 1;
  while((s & 1) == 0)
    s >>= 1;
  
  for(unsigned int i = 0; i < iters; i++) {
    _T a = rand() % (n - 1) + 1;
    _T temp = s;
    _T mod = mod_exp(a, temp, n);
    while(temp != n - 1 && mod != 1 && mod != n - 1)
    {
      mod = mul_mod(mod, mod, n);
      temp *= 2;
    }
    if(mod != n - 1 && temp % 2 == 0)
      return false;
  }
  return true; //probably
}
  
} } //namespace pbcpp::Math

/*! @} end doxygen groups*/

#endif //PB_MATH_HPP
