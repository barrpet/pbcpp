#ifndef PBCPP_MATH_CONSTANTS_HPP
#define PBCPP_MATH_CONSTANTS_HPP

namespace pbcpp
{

/*!
 *  \addtogroup math
 *  @{
 */
namespace math
{
  //! Templated mathematical functions
  template <typename _T = double>
  struct constants
  {
    static constexpr _T pi     = static_cast<_T>(3.141592653589793238462643383279502884L);
    static constexpr _T e      = static_cast<_T>(2.718281828459045235360287471352662497L);
    static constexpr _T phi    = static_cast<_T>(1.618033988749894848204586834365638117L);
    static constexpr _T sqrt2  = static_cast<_T>(1.414213562373095048801688724209698078L);
    static constexpr _T sqrt3  = static_cast<_T>(1.732050807568877293527446341505872366L);
    static constexpr _T degree = static_cast<_T>(0.017453292519943295769236907684886127L);
    static constexpr _T radian = static_cast<_T>(57.29577951308232087679815481410517033L);
    
    static constexpr _T zero      = static_cast<_T>(0.000000000000000000000000000000000000L);
    static constexpr _T sixteenth = static_cast<_T>(0.062500000000000000000000000000000000L);
    static constexpr _T tenth     = static_cast<_T>(0.100000000000000000000000000000000000L);
    static constexpr _T eigth     = static_cast<_T>(0.125000000000000000000000000000000000L);
    static constexpr _T fifth     = static_cast<_T>(0.200000000000000000000000000000000000L);
    static constexpr _T quarter   = static_cast<_T>(0.250000000000000000000000000000000000L);
    static constexpr _T third     = static_cast<_T>(0.333333333333333333333333333333333333L);
    static constexpr _T half      = static_cast<_T>(0.500000000000000000000000000000000000L);
    static constexpr _T one       = static_cast<_T>(1.000000000000000000000000000000000000L);
  };
  
} //namespace math

} //namespace pbcpp

/*! @} end doxygen groups*/

#endif //PBCPP_MATH_CONSTANTS_HPP

