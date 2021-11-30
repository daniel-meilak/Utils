#pragma once

#include<charconv>
#include<cmath>
#include<concepts>
#include<cstdlib>
#include<fstream>
#include<iostream>
#include<sstream>
#include<string>
#include<vector>

//=======================================================================================================
// Read input from file
//=======================================================================================================

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

   if (delimiters.empty()){
      std::cout << "No delimiters provided. Use read_input instead of read_input_2D" << std::endl;
      std::exit(EXIT_FAILURE);
   }

   // output vector of strings
   std::vector<std::vector<std::string>> input;

   // read input into "line"
   std::string line;
   std::ifstream input_file (file_name);

   // check that file exists
   if (!input_file.is_open()){
      std::cout << "Could not open file " << file_name << std::endl;
      std::exit(EXIT_FAILURE);
   }

   size_t line_length;
   size_t delims = delimiters.size();
   std::string temp_val;
   std::vector<std::string> temp_vector;
   while ( getline(input_file, line) ){

      line_length = line.size();

      // loop through contents of line
      for ( size_t read_pos=0; read_pos<line_length; read_pos++ ){

         for (size_t i=0; i<delims; i++){
            // if next characters match possible delimiters, skip delimiter and add to temp_vector
            if ( line.substr(read_pos, delimiters[i].size()) == delimiters[i]){
               read_pos += delimiters[i].size()-1;
               // in case delimiters follow each other
               if ( temp_val != "" ){ temp_vector.push_back(temp_val); }
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
      if (temp_val != ""){ temp_vector.push_back(temp_val); }

      // add vector to input
      input.push_back(temp_vector);
      temp_vector.clear();
      temp_val.clear();
   }

   input_file.close();

   return input;
}

//=======================================================================================================
// Convert vector type
//=======================================================================================================

// convert vector of strings to vector of ints
template <typename Int>
std::vector<Int> input_to_int(const std::vector<std::string> &input){

   std::vector<Int> output;
   Int value;
   output.reserve(input.size());
   
   for (const std::string &line : input){
      auto result = std::from_chars(line.data(), line.data()+line.size(), value);

      if (result.ec == std::errc::invalid_argument){
          std::cerr << "Non-integer value in input_to_int\n";
          std::exit(EXIT_FAILURE);
      }
      else if (result.ec == std::errc::result_out_of_range){
          std::cerr << "Integer type too small in input_to_int\n";
          std::exit(EXIT_FAILURE);
      }

      output.push_back(value);
   }

   return output;
}

// convert 2D vector of vector of strings to vector of vector of ints
std::vector<std::vector<int>> input_to_int_2D(const std::vector<std::vector<std::string>> &input){

   std::vector<std::vector<int>> output(input.size());
   size_t size = input.size();

   for (size_t i=0; i<size; i++){
      output[i].reserve(input[i].size());

      for (const std::string &word : input[i]){ output[i].push_back(std::stoi(word)); }
   }

   return output;
}

// convert 2D vector of vector of strings to vector of vector of long long ints
std::vector<std::vector<long long int>> input_to_llint_2D(const std::vector<std::vector<std::string>> &input){

   std::vector<std::vector<long long int>> output(input.size());
   size_t size = input.size();

   for (size_t i=0; i<size; i++){
      output[i].reserve(input[i].size());
      
      for (const std::string &word : input[i]){ output[i].push_back(std::stoll(word)); }
   }

   return output;
}

//=======================================================================================================
// Split functions
//=======================================================================================================

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

//=======================================================================================================
// TEMPLATES
//=======================================================================================================

// calculates the modulus such that negative numbers wrap around
template <typename T> T mod( T a, T b){ return (b + (a%b)) % b; }

//=======================================================================================================
// Sum and min/max element in 2D vectors
//=======================================================================================================

// sum values in column n of 2D square vector
template <typename T> T sum_col(const std::vector<std::vector<T>> &input, const size_t &n){
    T sum = 0;
    for (const std::vector<T> &line : input ){ sum += line[n]; }
    return sum;
}

// sum values in row n of 2D square vector
template <typename T> T sum_row(const std::vector<std::vector<T>> &input, const size_t &n){
    T sum = 0;
    for (const T &element : input[n] ){ sum += element; }
    return sum;
}

// min value in column n of 2D square vector
template <typename T> T min_col(const std::vector<std::vector<T>> &input, const size_t &n){
    T min = input[0][n];
    for (const std::vector<T> &line : input ){ min = std::min(min,line[n]); }
    return min;
}

// max value in column n of 2D square vector
template <typename T> T max_col(const std::vector<std::vector<T>> &input, const size_t &n){
    T max = input[0][n];
    for (const std::vector<T> &line : input ){ max = std::max(max,line[n]); }
    return max;
}

//=======================================================================================================
// Vector manhattan distance
//=======================================================================================================

// manhattan distance between two vectors of equal size
template <typename T> T manhattan(const std::vector<T> &lhs, const std::vector<T> &rhs){
    
    // check that vectors are the same size
    if (lhs.size()!=rhs.size()){
        std::cout << "Vectors must be equal size." << std::endl;
        std::exit(EXIT_FAILURE);
    }

    T distance = 0;

    const size_t size = lhs.size();
    for (size_t i=0; i<size; i++){ distance+= std::abs(rhs[i]-lhs[i]); }

    return distance;
}

// manhattan distance to origin
template <typename T> T manhattan(const std::vector<T> &point){

    T distance = 0;

    const size_t size = point.size();
    for (size_t i=0; i<size; i++){ distance+= std::abs(point[i]); }

    return distance;
}

// manhattan distance between two points (2D)
template <typename T> T manhattan(const T &x1, const T &y1, const T &x2=0, const T &y2=0){
    return std::abs(x2-x1) + std::abs(y2-y1);
}

//=======================================================================================================
// Cyclic container functions
//=======================================================================================================

// advance iterator cyclicly through container by n
template<typename It, typename Distance, typename Con>
constexpr void advance_cyclic(It &it, Distance n, Con &container){
    auto dist = typename std::iterator_traits<It>::difference_type(n);
    while (dist > 0){
        --dist;
        if (it == std::next(container.end(),-1)){ it = container.begin(); }
        else { it++; }
    }
    while (n < 0){
        ++n;
        if (it == container.begin()){ it = std::next(container.end(),-1); }
        else { it--; }
    }
}

// return iterator n steps ahead/behind, cyclicly in container
template<typename It, typename Distance, typename Con>
constexpr It next_cyclic(It it, const Distance &n, Con &container){
    advance_cyclic(it, n, container);

    return it;
}

//=======================================================================================================
// Grid functions
//=======================================================================================================

// count number of element in grid
template<typename Grid, typename Ele>
unsigned long long grid_count(const Grid &grid, const Ele element){

    unsigned long long count = 0;

    for (const auto &row : grid){
        for (const Ele box : row){
            if (box==element){ count++; }
        }
    }

    return count;
}

// display function for 2D grid
template<typename Grid> 
void display(const Grid &grid){

    for (const auto &row : grid){
        for (const auto pixel : row){
            std::cout << pixel;
        }
        std::cout << std::endl;
    }
}
