#ifndef PB_TIMER_HPP
#define PB_TIMER_HPP

//Check for C++11
#if __cplusplus <= 199711L
  #include <cstddef>
  #include <sys/time.h>
#else
  #define PB_CPP11
  #include <chrono>
  #include <ratio>
#endif

class Timer
{
  private:
    #ifdef PB_CPP11
    using namespace std::chrono;
    high_resolution_clock::time_point    tp_start;
    high_resolution_clock::time_point    tp_stop;
    #else
    struct timeval                       tp_start;
    struct timeval                       tp_stop;
    #endif
    bool                                 running;
  
  public:
    Timer() : is_running(false) { }
    ~Timer() { }
    
    bool is_running() const { return running; }
    
    
    void start();
    void stop();
    void reset();
    double elapsed_sec() const;
    
    void reset() {
      running = false;
      tp_stop = tp_start;
    }
    
    double elapsed_sec() const {
      if(running) {
        return duration_cast<duration<double>>(hr_clock::now() - tp_start).count();
      } else {
        return duration_cast<duration<double>>(tp_stop - tp_start).count();
      }
    }
};

Timer::Timer() : is_running(false)
{

}

Timer::~Timer()
{

}

#ifdef PB_CPP11 //C++11 Implementation
void Timer::start()
{
  tp_start = high_resolution_clock::now();
  running = true;
}

void Timer::stop()
{
  tp_stop = high_resolution_clock::now();
  running = false;
}

void Timer::reset()
{

}

double Timer::elapsed_sec() const
{
  if(running)
    return duration_cast<duration<double>>(high_resolution_clock::now() - tp_start).count();
  else
    return duration_cast<duration<double>>(tp_stop - tp_start).count();
}
#undef PB_CPP11
#else //C++ <= 98 Implementation
void Timer::start()
{

}

void Timer::stop()
{

}

void Timer::reset()
{

}

double Timer::elapsed_sec() const
{
  return 0.0L;`
}
#endif

#endif  //PB_TIMER_HPP
