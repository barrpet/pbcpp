/*******************************************************************************
MIT License
-----------

Copyright (c) 2015 Peter S. Barr
Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
*******************************************************************************/

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

class pbtimer
{
  private:
    #ifdef PB_CPP11
    std::chrono::high_resolution_clock::time_point    tp_start;
    std::chrono::high_resolution_clock::time_point    tp_stop;
    #else
    struct timeval                                    tp_start;
    struct timeval                                    tp_stop;
    #endif
  
  public:
    pbtimer();
    ~pbtimer();
    
    void start();
    void stop();
    double elapsed_sec() const;
};

pbtimer::pbtimer()
{

}

pbtimer::~pbtimer()
{

}

#ifdef PB_CPP11 //C++11 Implementation
void pbtimer::start()
{
  tp_start = std::chrono::high_resolution_clock::now();
}

void pbtimer::stop()
{
  tp_stop = std::chrono::high_resolution_clock::now();
}

double pbtimer::elapsed_sec() const
{
  return std::chrono::duration_cast<std::chrono::duration<double>>(tp_stop - tp_start).count();
}
#undef PB_CPP11
#else //C++ <= 98 Implementation
void pbtimer::start()
{
  gettimeofday(&tp_start, NULL);
}

void pbtimer::stop()
{
  gettimeofday(&tp_stop, NULL);
}

double pbtimer::elapsed_sec() const
{
  time_t esec = tp_stop.tv_sec - tp_start.tv_sec;
  suseconds_t eusec = tp_stop.tv_usec - tp_start.tv_usec ;
  return ((double) esec) + ((double) eusec) / 1000000.0L;
}
#endif  //PB_CPP11

#endif  //PB_TIMER_HPP
