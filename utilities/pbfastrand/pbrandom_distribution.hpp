#ifndef PB_RANDOM_DISTRIBUTIONS
#define PB_RANDOM_DISTRIBUTIONS

namespace pbrandom
{
  namespace distribution
  {
    template <typename RealType = double>
    class uniform_real
    {
      private:
        RealType a_;
        RealType b_;
      
      public:
        uniform_real() : a_(0), b(1) { }
        uniform_real(RealType a, RealType b) : a_(a), b_(b) { }
        uniform_real(const uniform_real<RealType>&) = default;
        uniform_real(uniform_real<RealType>&&) = default;
        uniform_real& operator=(const uniform_real<RealType>&) = default;
        uniform_real& operator=(uniform_real<RealType>&&) = default;
        ~uniform_real() { }
    };
  }
  
}

#endif
