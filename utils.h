#ifndef UTILS_H
#define UTILS_H

#include<vector>
#include<string>
#include<cmath>
#include<iostream>

//=======================================================================================================
// Read input from file
//=======================================================================================================

// read input file into vector of strings
std::vector<std::string> read_input(std::string file_name, std::string separator);

// read input file containing a single line of characters and remove any strings in "delimiters"
std::string read_line(std::string file_name, std::vector<std::string> delimiters);

// read input file into 2D vector or vectors
std::vector<std::vector<std::string>> read_input_2D(std::string file_name, std::vector<std::string> delimiters);

//=======================================================================================================
// Convert vector type
//=======================================================================================================

// convert strings vector to int
std::vector<int> input_to_int(const std::vector<std::string> &input);

// convert strings vector to long long int
std::vector<long long int> input_to_llint(const std::vector<std::string> &input);

// convert vec of vec of string to vec of vec of int
std::vector<std::vector<int>> input_to_int_2D(const std::vector<std::vector<std::string>> &input);

// convert vec of vec of string to vec of vec of long long ints
std::vector<std::vector<long long int>> input_to_llint_2D(const std::vector<std::vector<std::string>> &input);

//=======================================================================================================
// Split functions
//=======================================================================================================

// split string containing values separated by delimiter into vector of strings
std::vector<std::string> split(std::string str, std::string delimiter);

// separate input into multiple vectors according to delimiter spacing
std::vector<std::vector<std::string>> split_input(std::vector<std::string> input, std::string delimiter);

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

#endif /* UTILS_H */
