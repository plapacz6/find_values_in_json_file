/*
author: plapacz6@gmail.com
date: 2022-11-03
*/
#ifndef PRINT_RESULT_H
#define PRINT_RESULT_H

#include <string>
#include <unordered_map>
#include <vector>
namespace plapacz6_solution {

/**
 * @brief print 
 * 
 * @param cli_param - map of available options and their values
 *    -f   - json file to search throung
 *    -c   - number of results
 *    -p   - option of processing founded information
 *        -p field2occurrenceCount
 *        -p field2valuesSum
 *    //TODO:
 *    -s  -string describing name of field of summing value
 *    -u  -string identyfying one unit of json file (one json doc in file consisted jsons documents one per row)
 *    ////:TODO
 * @return int 
 */
int print_result(std::unordered_map<char, std::string> cli_param);

} //namespace plapacz6_solution

#endif //PRINT_RESULT_H