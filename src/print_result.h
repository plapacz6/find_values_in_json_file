/*
author: plapacz6@gmail.com
date: 2022-11-03
*/
#ifndef PRINT_RESULT_H
#define PRINT_RESULT_H

namespace plapacz6_solution {

struct cli_param_t;
int process_cli_param(int argc, char **argv, cli_param_t& cli_param);
int print_result(cli_param_t& cli_param);

} //namespace plapacz6_solution

#endif //PRINT_RESULT_H
