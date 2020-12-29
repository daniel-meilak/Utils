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

   int line_length;
   std::string temp_val;
   while ( getline(input_file, line) ){

      line_length = line.size();

      if ( separator == "" ){
         input.push_back(line);
      }
      else {
         // loop through contents of line
         for ( int read_pos=0; read_pos<line_length; read_pos++ ){

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

// Function to read input file "file_name" containing lines split by separator
// and output a vector of vector of strings called "input"
std::vector<std::vector<std::string>> read_input_2D(std::string file_name, std::string separator){

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

   int line_length;
   std::string temp_val;
   std::vector<std::string> temp_vector;
   while ( getline(input_file, line) ){

      line_length = line.size();

      if ( separator == "" ){
         std::cout << "Use read_input instead of read_input_2D" << std::endl;
         std::exit(EXIT_FAILURE);
      }
      else {
         // loop through contents of line
         for ( int read_pos=0; read_pos<line_length; read_pos++ ){

            // if next characters != separator, add next char to temp_val
            if ( line.substr(read_pos, separator.size()) != separator ){
               temp_val.push_back(line[read_pos]);
            }
            // else add the value to temp_vector and skip the separator
            else {
               read_pos += separator.size()-1;
               temp_vector.push_back(temp_val);
               temp_val.clear();
            }
         }
         // push_back last value
         temp_vector.push_back(temp_val);
         input.push_back(temp_vector);
         temp_vector.clear();
         temp_val.clear();
      }
   }

   input_file.close();

   return input;
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

   int line_length;
   std::string temp_val;
   std::vector<std::string> temp_vector;
   while ( getline(input_file, line) ){

      line_length = line.size();

      if ( delimiters.size() == 0 ){
         std::cout << "Use read_input instead of read_input_2D" << std::endl;
         std::exit(EXIT_FAILURE);
      }
      else {
         // loop through contents of line
         for ( int read_pos=0; read_pos<line_length; read_pos++ ){

            for (unsigned int i=0; i<delimiters.size(); i++){
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
         // push_back last value
         temp_vector.push_back(temp_val);
         input.push_back(temp_vector);
         temp_vector.clear();
         temp_val.clear();
      }
   }

   input_file.close();

   return input;
}

// convert vector of strings to vector of ints
std::vector<int> input_to_int(std::vector<std::string> input){

   std::vector<int> output;

   for (unsigned int i=0; i<input.size(); i++){
      output.push_back(std::stoi(input[i]));
   }

   return output;
}

// convert 2D vector of vector of strings to vector of vector of ints
std::vector<std::vector<int>> input_to_int_2D(std::vector<std::vector<std::string>> input){

   std::vector<std::vector<int>> output(input.size());

   for (unsigned int i=0; i<input.size(); i++){
      for (unsigned int j=0; j<input[i].size(); j++){
         
         output[i].push_back(std::stoi(input[i][j]));
      }
   }

   return output;
}

// convert vector of strings to vector of long long ints
std::vector<long long int> input_to_llint(std::vector<std::string> input){

   std::vector<long long int> output;

   for (unsigned int i=0; i<input.size(); i++){
      output.push_back(std::stoll(input[i]));
   }

   return output;
}

// convert vector of strings to vector of doubles
std::vector<double> input_to_double(std::vector<std::string> input){

   std::vector<double> output;

   for (unsigned int i=0; i<input.size(); i++){
      output.push_back(std::stod(input[i]));
   }

   return output;
}

// convert binary (represented as normal int) to decimal
int binary_to_decimal( int binary ){

   int decimal = 0;
   int i = 0;
   int remainder;

   while ( binary != 0 ){

      remainder = binary%10;
      binary /= 10;
      decimal += remainder*std::pow(2,i);
      ++i;
   }

   return decimal;
}

// convert deicmal to binary (as an int)
int decimal_to_binary( int decimal ){

   int binary = 0;
   int remainder, i = 1;

   while ( decimal != 0){
      remainder = decimal%2;
      decimal /= 2;
      binary += remainder*i;
      i *= 10;
   }

   return binary;
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

   std::vector<std::vector<std::string>> output;
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