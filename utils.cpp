#include"utils.h"
#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<string>
#include<cstdlib>
#include<cmath>

// Function to read input file "file_name" containing values separated by
// "separator" and output a vector of strings called "input"
std::vector<std::string> read_input(std::string file_name, std::string separator){

   // output vector of strings
   std::vector<std::string> input;

   // read input into "line"
   std::string line;
   std::ifstream input_file (file_name);

   // check that file exists
   if ( !(input_file.is_open()) ){
      std::cout << "Could not open file " << file_name << std::endl;
      std::exit(EXIT_FAILURE);
   }

   size_t line_length;
   std::string temp_val;
   while ( getline(input_file, line) ){

      line_length = line.size();

      if ( separator == "" ){ input.push_back(line); }
      else {
         // loop through contents of line
         for ( size_t read_pos=0; read_pos<line_length; read_pos++ ){

            // if next characters != separator, add next char to temp_val
            if ( line.substr(read_pos, separator.size()) != separator ){
               temp_val.push_back(line[read_pos]);
            }
            // else add the value to input and skip the separator
            else {
               read_pos += separator.size()-1;
               input.push_back(temp_val);
               temp_val.clear();
            }
         }
         // push_back last value
         input.push_back(temp_val);
         temp_val.clear();
      }
   }

   input_file.close();

   return input;
}

// Function to read input file "file_name" containing a single line of characters
// and remove any strings in "delimiters"
std::string read_line(std::string file_name, std::vector<std::string> delimiters){

   // output
   std::string output;

   // string to read input
   std::string line;
   std::ifstream input_file (file_name);

   // check that file exists
   if ( !(input_file.is_open()) ){
      std::cout << "Could not open file " << file_name << std::endl;
      std::exit(EXIT_FAILURE);
   }

   getline(input_file, line);

   size_t line_length = line.size();

   if (delimiters.empty()){ return line; }
   else {

      // loop through contents of line
      for ( size_t read_pos=0; read_pos<line_length; read_pos++ ){

         for (unsigned int i=0; i<delimiters.size(); i++){
            // if next characters match possible delimiters, skip delimiter
            if ( line.substr(read_pos, delimiters[i].size()) != delimiters[i]){
               read_pos += delimiters[i].size()-1;
               break;
            }
            // if next character does not match any delimiter, add to output
            else {
               if ( i == delimiters.size()-1 ){
                  output += line[read_pos];
               }
            }
         }
      }
   }

   input_file.close();

   return output;
}

// Function to read input file "file_name" containing lines split by multiple delimiters
// and output a vector of vector of strings called "input"
std::vector<std::vector<std::string>> read_input_2D(std::string file_name, std::vector<std::string> delimiters){

   // output vector of strings
   std::vector<std::vector<std::string>> input;

   // read input into "line"
   std::string line;
   std::ifstream input_file (file_name);

   // check that file exists
   if ( !(input_file.is_open()) ){
      std::cout << "Could not open file " << file_name << std::endl;
      std::exit(EXIT_FAILURE);
   }

   size_t line_length;
   size_t delims = delimiters.size();
   std::string temp_val;
   std::vector<std::string> temp_vector;
   while ( getline(input_file, line) ){

      line_length = line.size();

      if (delimiters.empty()){
         std::cout << "Use read_input instead of read_input_2D" << std::endl;
         std::exit(EXIT_FAILURE);
      }
      else {
         // loop through contents of line
         for ( size_t read_pos=0; read_pos<line_length; read_pos++ ){

            for (size_t i=0; i<delims; i++){
               // if next characters match possible delimiters, skip delimiter and add to temp_vector
               if ( line.substr(read_pos, delimiters[i].size()) == delimiters[i]){
                  read_pos += delimiters[i].size()-1;
                  // in case delimiters follow each other
                  if ( temp_val != "" ){
                     temp_vector.push_back(temp_val);
                  }
                  temp_val.clear();
                  break;
               }
               // if next character does not match any delimiter, add to temp_val
               else {
                  if ( i == delimiters.size()-1 ){
                     temp_val.push_back(line[read_pos]);
                  }
               }
            }
         }
         // push_back last value (if not empty)
         if ( temp_val != ""){
            temp_vector.push_back(temp_val);
         }
         // add vector to input
         input.push_back(temp_vector);
         temp_vector.clear();
         temp_val.clear();
      }
   }

   input_file.close();

   return input;
}

// convert vector of strings to vector of ints
std::vector<int> input_to_int(const std::vector<std::string> &input){

   std::vector<int> output(input.size());
   for (const std::string &line : input){ output.push_back(std::stoi(line)); }

   return output;
}

// convert 2D vector of vector of strings to vector of vector of ints
std::vector<std::vector<int>> input_to_int_2D(const std::vector<std::vector<std::string>> &input){

   std::vector<std::vector<int>> output(input.size());
   size_t size = input.size();

   for (size_t i=0; i<size; i++){
      output[i].resize(input[i].size());

      for (const std::string &word : input[i]){ output[i].push_back(std::stoi(word)); }
   }

   return output;
}

// convert 2D vector of vector of strings to vector of vector of long long ints
std::vector<std::vector<long long int>> input_to_llint_2D(const std::vector<std::vector<std::string>> &input){

   std::vector<std::vector<long long int>> output(input.size());
   size_t size = input.size();

   for (size_t i=0; i<size; i++){
      output[i].resize(input[i].size());
      
      for (const std::string &word : input[i]){ output[i].push_back(std::stoll(word)); }
   }

   return output;
}

// convert vector of strings to vector of long long ints
std::vector<long long int> input_to_llint(const std::vector<std::string> &input){

   std::vector<long long int> output(input.size());

   for (const std::string &line : input){ output.push_back(std::stoll(line)); }

   return output;
}

// convert vector of strings to vector of doubles
std::vector<double> input_to_double(const std::vector<std::string> &input){

   std::vector<double> output;

   for (unsigned int i=0; i<input.size(); i++){
      output.push_back(std::stod(input[i]));
   }

   return output;
}

// split delimiter spaced elements in string into vector of strings
std::vector<std::string> split(std::string str, std::string delimiter){ 

   size_t pos = 0;
   std::string token;
   std::vector<std::string> output;

   while ((pos = str.find(delimiter)) != std::string::npos){
      token = str.substr(0, pos);
      output.push_back(token);
      str.erase(0, pos + delimiter.length());
   }
   output.push_back(str);
 
   return output; 
}

// takes input and splits into multiple vectors according to delimiter
std::vector<std::vector<std::string>> split_input(std::vector<std::string> input, std::string delimiter){

   std::vector<std::vector<std::string>> output(input.size());
   std::vector<std::string> part;

   for (std::string line : input){
      if ( line != delimiter){
         part.push_back(line);
      }
      else {
         output.push_back(part);
         part.clear();
      }
   }
   output.push_back(part);

   return output;
}