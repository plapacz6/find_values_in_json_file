/*
author:plapacz6@gmail.com
date:2022-11-09
*/

#include "print_result.h"

int main(int argc, char **argv){    
    plapacz6_solution::cli_param_t cli_param;
    
    plapacz6_solution::process_cli_param(argc, argv, cli_param);
    
    return plapacz6_solution::print_result(cli_param);
}
