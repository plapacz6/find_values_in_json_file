/*
author: plapacz6@gmail.com
date: 2022-11-03
*/
#include "rapidjson/writer.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/reader.h"
#include "rapidjson/error/en.h"

#include <fstream>
#include <sstream>
#include <exception>
#include <iostream>
#include <iomanip> 
#include <numeric>
#include <string>
#include <cstdint>
#include <algorithm>

#include "solution.h"

namespace plapacz6_solution {

// struct json_fields_value_t {
//   long json_docValue_longlong;
//   std::string json_categoryName_str;
// };
json_fields_value_t::json_fields_value_t(){
  this->clear();
}
void json_fields_value_t::clear(){  
  json_docValue_longlong = 0;
  json_categoryName_str = "";  
}
#ifdef DEBUG
std::ostream& operator<<(std::ostream& os, const json_fields_value_t& obj){  
  os << "json_docValue_longlong: " << obj.json_docValue_longlong << "\n";
  os << "json_categoryName_str     : " << obj.json_categoryName_str << "\n";
  return os;
}
#endif //DEBUG



void count_docSameCategory_occurrence
    (std::vector<json_fields_value_t>& values, 
    std::vector<result_values_t>& counted_values)
{    
  for(std::vector<json_fields_value_t>::iterator itv = values.begin(); itv != values.end(); itv++){  
    bool json_unit_found = false;
    for(std::vector<result_values_t>::iterator itc = counted_values.begin(); itc != counted_values.end(); itc++){
  
      if(itc->categoryName == itv->json_categoryName_str){
        itc->count++;
        
        #ifndef FIIELD2_DOUBLE                
        itc->costs += static_cast<uint64_t>(itv->json_docValue_longlong);
        #else        
        itc->costs += static_cast<double>(itv->json_docValue_longlong);
        #endif// FIIELD2_DOUBLE

        json_unit_found = true;
        break;
      }
    }
    if(!json_unit_found){
      #ifndef FIIELD2_DOUBLE
      counted_values.emplace_back(result_values_t(itv->json_categoryName_str, 1, itv->json_docValue_longlong));                  
      #else      
      counted_values.emplace_back(result_values_t(
        itv->json_categoryName_str, 1, static_cast<double>(itv->json_docValue_longlong)));            
      #endif
    }
  }  
}



/**
 * @brief parse a file with many json documents, each on a separate line
 * 
 * @param cli_param - command line options
 * @param values - vector of raw selected data from json 
 * @param counted_values - vector of processed selected data from json 
 */
void find_solv_doc(
    cli_param_t& cli_param, 
    std::vector<json_fields_value_t>& values,
    std::vector<result_values_t>& counted_values)
{     
  rapidjson::Document doc;  
  std::string json_record_string;
  json_fields_value_t current_value;

  const char *json_categoryName_str = cli_param.m[cli_param.o.catName];
  const char *json_docValue_longlong = cli_param.m[cli_param.o.valName];

  std::ifstream  ifstm;  
  ifstm.open(cli_param['f'], std::ios::in);
  if(!ifstm.is_open()) {
    throw std::ios_base::failure("problem with opening " + cli_param.m[cli_param.o.fname.s] +" file");
  }
  counted_values.clear();
  values.clear();
  
  /*
  The processing is based on the assumption that
  each line in file.json input is one json document.  
  */
  
  while(std::getline(ifstm, json_record_string)){
    
    doc.Parse(json_record_string.c_str());    
    
    current_value.clear();
    
    if(!doc.HasParseError()){
      
      assert(doc.HasMember(json_categoryName_str));
      assert(doc.HasMember(json_docValue_longlong));
      assert(doc[json_categoryName_str].IsString());
      assert(doc[json_docValue_longlong].IsInt64());

      current_value.json_categoryName_str = doc[json_categoryName_str].GetString();
      current_value.json_docValue_longlong = doc[json_docValue_longlong].GetInt64();      

      values.emplace_back(current_value);
      #ifdef DEBUG
        std::cout << current_value << std::endl;      
      #endif //DEBUG
      current_value.clear();
    }
    else{     
        std::stringstream msg;
        size_t o = doc.GetErrorOffset();        
        msg << "Error: " << rapidjson::GetParseError_En(doc.GetParseError()) << std::endl;;
        msg << " at offset " << o << " near '" 
            << std::string(json_record_string).substr(o, 10) << "...'" << std::endl;
        throw json_syntax_error_exception(msg.str().c_str());        
    }    
  }//while
    
  #ifdef DEBUG
  for (std::vector<json_fields_value_t>::iterator it = values.begin(); it != values.end(); it++){        
    std::cout << *it << std::endl;
  }
  #endif // DEBUG

  count_docSameCategory_occurrence(values, counted_values);
  
  ifstm.close();  
}



std::string&& opt_name_t::get_opt_str4getopt(){
  std::string opts = "";
  opts += this->fname.o + ":";
  opts += this->nresult.o + ":";
  opts += this->procOccur.o + ":";
  opts += this->catName.o + ":";
  opts += this->valName.o + ":";
  return opts;
}



int process_cli_param(int argc, char **argv, cli_param_t& cli_param){
  cli_param.o = {
  'f', nullptr,
  'c', nullptr,
  't', "category_occuranceCount",
  't', "category_valueSum",
  'k', nullptr,
  'v', nullptr,
  };
  std::string options = cli_param.o.get_opt_str4getopt();
  int opt_char = 0;
  /* from <unistd.h>
  optarg - argument founded opiton
  */
  while( (opt_char = getopt(arc, argv, options.c_str()) != -1){
    if(opt_char == '?') {
      std::cout << "Usage: \n" 
      << argv[0] << " -f json_file -k category_field_name -v value_field_name" << std::endl;
      << "
 *  available options and their values
 *    -f   - json file to search throung (one json doc per row in file)
 *    -c   - number of results
 *    -t   - option of processing founded information
 *        -t category_occuranceCount
 *        -t category_valueSum
 *    //TODO:
 *    -k  -string representing name of field category's name (one per json doc)
 *    -v  -string representing name of field holding value (one per json doc)";
      std::cout << std::endl;
      return -1;
    }
    cli_param.m[opt_char] = optarg;
  }
  return 0;
}



/**
 * @brief print 
 * 
 * @param cli_param - map of available options and their values
 *    -f   - json file to search throung (one json doc per row in file)
 *    -c   - number of results
 *    -t   - option of processing founded information
 *        -t category_occuranceCount
 *        -t category_valueSum
 *    //TODO:
 *    -k  -string representing name of field category's name (one per json doc)
 *    -v  -string representing name of field holding value (one per json doc)
 *    ////:TODO
 * @return int 
 */

int print_result(cli_param_t& cli_param){
  try{
    std::size_t max_values = UINT_MAX; 
    if(!cli_param['c'].empty()){
      int value_c = std::stol(cli_param.m[cli_param.o.nresult.c]); 
      if(value_c < 0) 
        throw std::invalid_argument("number_of_results is lower than 0");
      max_values = value_c;
    }

    std::vector<json_fields_value_t> values;
    values.clear();
    std::vector<result_values_t> counted_values;
    counted_values.clear();

    find_solv_doc(cli_param, values, counted_values);
    
    if(cli_param[cli_param.o.procOccur.c] == cli_param.o.procOccur.s){
      //counting occurence of json docs with the same category
    
      std::sort(counted_values.begin(), counted_values.end(), sort_by_count<result_values_t>);

      for(int i = 0; i < max_values && i < counted_values.size();  i++)
        std::cout << counted_values[i].count << " " << counted_values[i].categoryName << "\n";
      std::cout << std::endl;
    }
    else    
    if(cli_param[cli_param.o.procOccur.c] == cli_param.o.procSum.s){
      //summing values of doc from the same category

      std::sort(counted_values.begin(), counted_values.end(), sort_by_values<result_values_t>);

      for(int i = 0; i < max_values && i < counted_values.size();  i++)
          std::cout 
          #ifdef FIIELD2_DOUBLE
          << std::setprecision(2) << std::fixed 
          #endif
          <<  counted_values[i].costs 
          << " " << counted_values[i].categoryName << "\n";
      std::cout << std::endl;
    }
    else{   
      //simple printout raw founded values without summing or counting       
            
      std::sort(values.begin(), values.end(), sort_by_json_docValue_longlong<json_fields_value_t>);

      for(int i = 0; i < max_values && i < values.size();  i++)
        std::cout << values[i].json_docValue_longlong << " " << values[i].json_categoryName_str << "\n";
      std::cout << std::endl;
    }  
  }
  catch(json_syntax_error_exception& msg){
      std::cerr << msg.what() << std::endl;
      return EXIT_FAILURE;
  }
  catch(std::invalid_argument& msg ){
      std::cerr << msg.what() << "\n" << "number_of_results must be number > 0 and < " << UINTMAX_MAX<< std::endl;
      return EXIT_FAILURE;
  }
  catch(std::out_of_range& msg ){
      std::cerr << msg.what() << "\n" << "number_of_results must be number > 0 and < " << UINTMAX_MAX<< std::endl;
      return EXIT_FAILURE;
  }
  catch(const std::ios_base::failure& msg){
      std::cerr << msg.what() << std::endl;      
      return EXIT_FAILURE;
  }
  catch(...){
      return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
  
} //namespace plapacz6_solution
