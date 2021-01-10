#ifndef UTILS_H
#define UTILS_H

#include<vector>
#include<string>
#include<cmath>

// read input file into vector of strings
std::vector<std::string> read_input(std::string file_name, std::string separator);

// read input file containing a single line of characters and remove any strings in "delimiters"
std::string read_line(std::string file_name, std::vector<std::string> delimiters);

// read input file into 2D vector or vectors
std::vector<std::vector<std::string>> read_input_2D(std::string file_name, std::vector<std::string> delimiters);

// separate input into multiple vectors according to delimiter spacing
std::vector<std::vector<std::string>> split_input(std::vector<std::string> input, std::string delimiter);

// convert strings vector to int
std::vector<int> input_to_int(std::vector<std::string> input);

// convert strings vector to long long int
std::vector<long long int> input_to_llint(std::vector<std::string> input);

// convert strings vector to double
std::vector<double> input_to_double(std::vector<std::string> input);

// convert vec of vec of string to vec of vec of int
std::vector<std::vector<int>> input_to_int_2D(std::vector<std::vector<std::string>> input);

// binary to decimal converter
int binary_to_decimal( int binary );

// decimal to binary converter
int decimal_to_binary( int decimal );

// split string containing values separated by delimiter into vector of strings
std::vector<std::string> split(std::string str, std::string delimiter);

// TEMPLATES

// calculates the modulus such that negative numbers wrap around
template <typename T> T mod( T a, T b){ return (b + (a%b)) % b; }

// sum values in column n of 2D square vector
template <typename T> T sum_col(const std::vector<std::vector<T>> &input, const size_t &n){
    T sum = 0;
    for ( std::vector<T> line : input ){ sum += line[n]; }
    return sum;
}

// sum values in row n of 2D square vector
template <typename T> T sum_row(const std::vector<std::vector<T>> &input, const size_t &n){
    T sum = 0;
    for ( T element : input[n] ){ sum += element; }
    return sum;
}

// manhattan distance between two points (2D)
template <typename T> T manhattan_dist(const T &x1, const T &y1, const T &x2, const T &y2){
    return (x2-x1) + (y2-y1);
}

// euclidian distance between two points (2D)
template <typename T> T euclidian_dist(const T &x1, const T &y1, const T &x2, const T &y2){
    return std::sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
}

#endif /* UTILS_H */
