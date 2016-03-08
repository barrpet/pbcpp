#ifndef PBCPP_DATETIME_MATCH_HPP
#define PBCPP_DATETIME_MATCH_HPP

#include <string>
#include <regex>

#ifdef DEBUG
#include <iostream>
#endif

namespace pbcpp {

class DateTimeMatch
{
private:
  const std::string yrr_regex = "(19|20)[0-9]{2}";
  const std::string mon_regex = "((0[1-9])|(1|[0-2]))";
  const std::string day_regex = "((0[1-9])|([1-2][0-9])|(3[0-1]))";
  const std::string hrr_regex = "[0-5][0-9]";
  const std::string min_regex = "[0-5][0-9]";
  const std::string sec_regex = "[0-9]{3}";
  const std::regex time_regex =
    std::regex("((?:[0-1][0-9])|(?:[2][0-3]))" //hours
               "[^0-9]*"
               "([0-5][0-9])" //minutes
               "[^0-9]*"
               "([0-5][0-9])" //seconds
               "[^0-9]*"
               "([0-9]{3})", //milliseconds
               std::regex::optimize);
  
public:

  bool hasTime(std::string& str)
  {
    //std::basic_regex<char> br(std::string(hrr_regex + "[^0-9]*" + min_regex + "[^0-9]*" + sec_regex));
    std::smatch mr;
    bool res = std::regex_search(str, mr, time_regex);
    #ifdef DEBUG
    std::cout << "*****************************\n";
    for(auto& m : mr)
      std::cout << m.str() << "\n";
    std::cout << "*****************************\n";
    #endif
    return res;
  }
  
}; //class DateTimeMatch

} //namespace pbcpp

#endif //PBCPP_DATETIME_MATCH_HPP
