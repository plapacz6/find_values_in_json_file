/*
author: plapacz6@gmail.com
date: 2022-11-03
*/
#ifndef SOLUTION_H
#define SOLUTION_H

#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <unistd.h>

#include "print_result.h"
namespace plapacz6_solution {

//#define DEBUG


struct opt1_t{
  char c;  //option character
  char *s; //allowed value (nullptr - value is user dependent)
};
struct opt_name_t {
  opt1_t fname;
  opt1_t nresult;
  opt1_t procOccur;
  opt1_t procSum;
  opt1_t catName;
  opt1_t valName;
  std::string&& get_opt_str4getopt();
};
struct cli_param_t {
  std::unordered_map<char, std::string> m;
  opt_name_t o;  
};
// --------------------------------



class json_syntax_error_exception : public std::invalid_argument {
  public:
    json_syntax_error_exception(const char* what_arg): std::invalid_argument(what_arg) {}    
};



struct json_fields_value_t 
{  
  uint32_t json_docValue_longlong;
  std::string json_categoryName_str;  
  json_fields_value_t();
  void clear();
};

template<typename T> //requires json_docValue_longlong
bool sort_by_json_docValue_longlong(T& a, T& b){
  return a.json_docValue_longlong > b.json_docValue_longlong;
}  
#ifdef DEBUG
std::ostream& operator<<(std::ostream& os, const json_fields_value_t& obj);
#endif // DEBUG


template <typename T>
struct result_values_t_template{
  std::string categoryName;
  uint32_t count;
  T costs;    
  result_values_t_template(std::string categoryName_, uint32_t count_, T costs_) :
     categoryName(categoryName_), count(count_), costs(costs_)
  {}  
  void clear(){
    categoryName = "";
    costs = 0;
    count = 0;
  }  
};

//#define FIIELD2_DOUBLE
#ifdef FIIELD2_DOUBLE
typedef result_values_t_template<double> result_values_t;
#else
typedef result_values_t_template<uint64_t > result_values_t;
#endif

template <typename T> //requires costs
bool sort_by_values(T& a, T& b){
  return a.costs > b.costs;
}
template<typename T> //requires count
bool sort_by_count(T& a, T& b){
  return a.count > b.count;
}  



void count_docSameCategory_occurrence
    (std::vector<json_fields_value_t>& values, 
    std::vector<result_values_t>& counted_values);
              
void find_solv_doc(
    std::unordered_map<char, std::string> parameters, 
    std::vector<json_fields_value_t>& values,
    std::vector<result_values_t>& counted_values);

} //namespace plapacz6_solution
#endif // SOLUTION_H
