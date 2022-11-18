/*
author:plapacz6@gmail.com
date:2022-11-09
*/

#include "print_result.h"

int main(int argc, char **argv){    
    plapacz6_solution::cli_param_t cli_param;
    
    if(! plapacz6_solution::process_cli_param(argc, argv, cli_param)){
      std::exit(1)
    }
    
    return plapacz6_solution::print_result(cli_param);
}
