#include <iostream>
#include <unistd.h>
#include "pbtimer.hpp"

int main(int argc, const char** argv)
{
  pbtimer timer;
  timer.start();
  sleep(2);
  timer.stop();
  
  std::cout << "Expect approx. 2.0.\n";
  std::cout << timer.elapsed_sec() << std::endl;
  
  return 0;
}
