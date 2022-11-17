/*
author: plapacz6@gmail.com
date: 2022-11-03
*/
#ifndef PRINT_RESULT_H
#define PRINT_RESULT_H

#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <unistd.h>
namespace plapacz6_solution {

struct opt1_t{
  char c;
  char *s;
};
struct opt_name_t {
  opt1_t fname;
  opt1_t nresult;
  opt1_t procOccur;
  opt1_t procSum;
  opt1_t catName;
  opt1_t valName;
};

struct cli_param_t {
  std::unordered_map<char, std::string> m;
  opt_name_t o;  
};

int process_cli_param(int argc, char **argv, cli_param_t& cli_param);
int print_result(cli_param_t& cli_param);

} //namespace plapacz6_solution

#endif //PRINT_RESULT_H