#ifndef PB_MATH_HPP
#define PB_MATH_HPP

/*!
 *  \addtogroup pbmath
 *  @{
 */

//! Templated mathematical functions
namespace pbmath
{
  //Constants
  constexpr double pi()     { return 3.141592653589793238462643383279502884L; }
  constexpr double e()      { return 2.718281828459045235360287471352662497L; }
  constexpr double phi()    { return 1.618033988749894848204586834365638117L; }
  constexpr double sqrt2()  { return 1.414213562373095048801688724209698078L; }
  constexpr double sqrt3()  { return 1.732050807568877293527446341505872366L; }
  constexpr double degree() { return 0.017453292519943295769236907684886127L; }
  constexpr double radian() { return 57.29577951308232087679815481410517033L; }
  

  /*! \fn int_type gcd(int_type u, int_type v)
   * \brief Return the greatest common divisor of two integers
   * \param u an integer (preferably unsigned)
   * \param v an integer (preferably unsigned)
   * \return \a gcd returns the greatest common divisor if two input integers
   */
  template <class int_type>
  int_type gcd(int_type u, int_type v) {
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
        int_type t = v;
        v = u;
        u = t;
      }
      v = v - u;
    }while(v != 0);
    return u << shift;
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
  
  /*! \fn bool is_prime_miller_rabin(int_type n)
   * \brief Returns whether or not a number is probably prime
   * \param n The integer to test for primality
   * \param iters The number of iterations to run the test for
   * \return Technically returns either false or probably true
   */
  template <class int_type>
  bool is_prime_miller_rabin(int_type n, unsigned iters = 25)
  {
    if(n < 2) { return false; }
    if(n == 2) { return true; }
    if((n & 1) == 0) { return false; }
    
    int_type s = n - 1;
    while((s & 1) == 0)
      s >>= 1;
    
    for(unsigned i = 0; i < iters; i++) {
      int_type a = rand() % (n - 1) + 1;
      int_type temp = s;
      int_type mod = mod_exp(a, temp, n);
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
  
} //end namespace pbmath

/*! @} end doxygen groups*/

#endif //PB_MATH_HPP
