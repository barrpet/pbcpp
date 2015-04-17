#ifndef PB_FAST_RAND
#define PB_FAST_RAND

#include <chrono>
#include <cstdint>
#include <cmath>

/* 16 Random 64-bit unsigned ints from Random.org
 * https://xkcd.com/221/  */
#define RAND_SEED \
0x3defc96632ef02b9, \
0x8e90363c0e17b94f, \
0xa475bebf725d5637, \
0x0a730a049bf3226e, \
0xf4ae35c08c925568, \
0xef7ad28ad649d06f, \
0xae7bad73c3749a5c, \
0x58e7ab85e6bc90c8, \
0x2b9ffce661908871, \
0xb6f9013a41f3483c, \
0x59cdd885b0a75528, \
0x7ba6bac4b645578c, \
0x70d174668607356f, \
0x1f9bf4c0ac86d9d8, \
0x6edb83c3ed843533

class pbfastrand
{
  private:
    //State infomation
    uint64_t state[16]{RAND_SEED};
    unsigned p = 0;
    
    //For generating normal
    double z0 = 0;
    double z1 = 0;
    bool do_gen_unif = false;
    
    //For generating 32bit
    uint64_t rand_64 = 0;
    bool do_gen_32 = false;
    
    //Constants
    static constexpr double epsilon = std::numeric_limits<double>::min();
    static constexpr double two_pi = 2.0 * 3.14159265358979323846L;
    
  public:
    pbfastrand() { }
    ~pbfastrand() { }
    
    //No copying
    pbfastrand(const pbfastrand&) = delete;
    pbfastrand(const pbfastrand&&) = delete;
    pbfastrand& operator=(const pbfastrand&) = delete;
    pbfastrand& operator=(const pbfastrand&&) = delete;
    
    //Seed using small xorshift with current time
    void seed()
    {
      uint64_t s =
        std::chrono::duration_cast<std::chrono::milliseconds>
        (std::chrono::system_clock::now().time_since_epoch()).count();
      for(auto i = 0; i < 16; i++)
      {
        s ^= s >> 12;
        s ^= s << 25;
        s ^= s >> 27;
        state[i] = s * 2685821657736338717ull;
      }
    }
    
    //Seed using an array of 64 bit unsigned ints
    //If n > 16, we just take the first 16
    void seed(uint64_t* seed_arr, size_t n)
    {
      size_t len = (n < 16) ? n : 16;
      for(unsigned i = 0; i < len; i++)
        state[i] = seed_arr[i];
    }
    
    //Standard generate
    uint64_t gen()
    {
      uint64_t s0 = state[p];
      uint64_t s1 = state[p = (p+1) & 15];
      s1 ^= s1 << 31;
      s1 ^= s1 >> 11;
      s0 ^= s0 >> 30;
      return (state[p] = s0 ^ s1) * 1181783497276652981ull;
    }
    
    //Generates a signed 32 bit integer
    int32_t gen_int32()
    {
      uint32_t rnd = gen_uint32();
      return *(int32_t*)(&rnd);
    }
    
    //Generates an unsigned 32 bit integer
    //Just takes half the bits from a 64 bit
    uint32_t gen_uint32()
    {
      uint32_t rnd;
      
      do_gen_32 = !do_gen_32;
      
      if(!do_gen_32)
        return rand_64 & UINT32_MAX;
      
      rand_64 = gen();
      rnd = rand_64 & UINT32_MAX;
      rand_64 >>= 32;
      
      return rnd;
    }
    
    //Generates a signed 64 bit integer
    int64_t gen_int64()
    {
      uint64_t rnd = gen();
      return *(int64_t*)(&rnd);
    }
    
    //Generates an unsigned 64 bit integer
    inline uint64_t gen_uint64()
    {
      return gen();
    }
    
    //Generate a uniformly distributed random double in [0,1]
    double gen_unif()
    {
      uint64_t rand64 = gen_uint64();
      return (double)rand64 * (1.0L / UINT64_MAX);
    }
    
    
    //Generate a normally distributed random double
    double gen_norm(double mu = 0.0L, double sigma = 1.0L)
    {
      do_gen_unif = !do_gen_unif;
      if(!do_gen_unif)
        return z1 * sigma + mu;
      double u1, u2;
      do
      {
        u1 = gen_unif();
        u2 = gen_unif();
      } while(u1 <= epsilon);
      z0 = sqrt(-2.0 * log(u1)) * cos(two_pi * u2);
      z1 = sqrt(-2.0 * log(u1)) * sin(two_pi * u2);
      return z0 * sigma + mu;
    }
    
    
    //Generates a chi-squared random double
    //Sum of k squared standard normal random variables
    double gen_chisq(unsigned k)
    {
      double res = 0.0L;
      for(unsigned i = 0; i < k; i++)
      {
        double x = gen_norm();
        res += (x * x);
      }
      return res;
    }
    
    //Beta
    double gen_beta(double alpha, double beta)
    {
      double gamm = tgamma(alpha + beta) / (tgamma(alpha) * tgamma(beta));
      double max_x = (alpha - 1.0L) / (alpha + beta - 2.0L);
      double max_y = gamm * pow(max_x, alpha - 1.0L) * pow(1.0L - max_x, beta - 1.0L);
      
      double res, u, y;
      do
      {
        u = gen_unif();
        y = gen_unif();
        res = gamm * pow(y, alpha - 1.0L) * pow(1.0L - y, beta - 1.0L);
      } while(u > (res / max_y));
      return y;
    }
    
    //Generates an exponential random double
    //Amount of time between events in a Poisson process
    //with const avg time between events lambda
    double gen_exp(double lambda)
    {
      double u1 = gen_unif();
      while(u1 <= epsilon)
        u1 = gen_unif();
      return (-1.0L / lambda) * log(1.0L - u1);
    }
    
    //Erlang
    //Sum of n independent exponentials with mean 1/lambda
    template <typename IntType=unsigned>
    double gen_erlang(IntType n, double lambda)
    {
      double mult = 1.0L;
      for(auto i = 0; i < n; i++)
        mult *= gen_unif();
      return (-1.0L / lambda) * log(mult);
    }
    
    //Generates a random Poisson variable
    //Number of events occuring in a const time interval with rate lambda
    template <typename IntType=unsigned>
    IntType gen_poisson(double lambda)
    {
      IntType res(0);
      double mult = 1.0L;
      while((mult *= gen_unif()) > exp(-1.0L * lambda))
        res++;
      return res;
    }
    
    //Generates a bernoulli random trial with success p
    //1 if success, 0 if failure, probability p
    template <typename IntType=int>
    inline IntType gen_bernoulli(double p)
    {
      return (gen_unif() < p) ? IntType(1) : IntType(0);
    }
    
    //Generates a binomial random variable with success p and n trials
    //Number of successes in n indpendent trials each with probability p
    template <typename IntType=unsigned>
    IntType gen_binomial(double p, IntType n)
    {
      IntType res(0);
      for(auto i = 0; i < n; i++)
        res += gen_bernoulli(p);
      return res;
    }
    
    //
    template <typename IntType=unsigned>
    inline IntType gen_geometric(double p)
    {
      return floor(log(gen_unif()) / log(1.0L - p));
    }
    
    //Number of failures before the nth success of bernoulli trials
    //with probablity of success p
    template <typename IntType=unsigned>
    IntType gen_negbinomial(double p, IntType n)
    {
      IntType res(0);
      for(auto i = 0; i < n; i++)
        res += gen_geometric<IntType>(p);
      return res;
    }
};  //end class pbfastrand

#undef RAND_SEED
#endif //PB_FAST_RAND
