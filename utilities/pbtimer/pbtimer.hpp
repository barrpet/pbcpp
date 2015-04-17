#ifndef PB_TIMER_HPP
#define PB_TIMER_HPP

#include <chrono>
#include <ratio>

class Timer
{
  using namespace std::chrono;
  typedef high_resolution_clock hr_clock;
  
  
  private:
    hr_clock::time_point    tp_start;
    hr_clock::time_point    tp_stop;
    bool                    running;
  
  public:
    Timer() : is_running(false) { }
    
    void start() {
      tp_start = hr_clock::now();
    }
    
    void stop() {
      tp_stop = hr_clock::now();
      running = false;
    }
    
    void reset() {
      running = false;
      tp_stop = tp_start;
    }
    
    bool is_running() { return running; }
    
    double elapsed_sec() const {
      if(running) {
        return duration_cast<duration<double>>(hr_clock::now() - tp_start).count();
      } else {
        return duration_cast<duration<double>>(tp_stop - tp_start).count();
      }
    }
    
    unsigned long elapsed_usec() const;
};

#endif
