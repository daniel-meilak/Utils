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

// convert vec of vec of string to vec of vec of long long ints
std::vector<std::vector<long long int>> input_to_llint_2D(std::vector<std::vector<std::string>> input);

// binary to decimal converter
int binary_to_decimal( int binary );

// decimal to binary converter
int decimal_to_binary( int decimal );

// split string containing values separated by delimiter into vector of strings
std::vector<std::string> split(std::string str, std::string delimiter);

//=======================================================================================================
// TEMPLATES
//=======================================================================================================

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

// manhattan distance between two points(3D)
template <typename T> T manhattan_3D(const T &x1, const T &y1, const T &z1, const T &x2=0, const T &y2=0, const T &z2=0){
    return std::abs(x2-x1) + std::abs(y2-y1) + std::abs(z2-z1);
}

// manhattan distance between two points (2D)
template <typename T> T manhattan_2D(const T &x1, const T &y1, const T &x2=0, const T &y2=0){
    return std::abs(x2-x1) + std::abs(y2-y1);
}

// euclidian distance between two points(3D)
template <typename T> T euclidian_3D(const T &x1, const T &y1, const T &z1, const T &x2=0, const T &y2=0, const T &z2=0){
    return std::sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) + (z2-z1)*(z2-z1));
}

// euclidian distance between two points (2D)
template <typename T> T euclidian_2D(const T &x1, const T &y1, const T &x2=0, const T &y2=0){
    return std::sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
}

// advance iterator cyclicly through container by n
template<typename It, typename Distance, typename Con>
constexpr void advance_cyclic(It &it, Distance n, Con &container){
    auto dist = typename std::iterator_traits<It>::difference_type(n);
    while (dist > 0){
        --dist;
        if (it == std::next(container.end(),-1)){ it = container.begin(); }
        else { it++; }
    }
    while (dist < 0){
        ++dist;
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

// checks if a number is prime
template<typename T> bool is_prime(T n){
    if (n <= 1){ return false; }

    for (T i=2; i<n; i++){
        if (n % i == 0){
            return false;
        }
    }

    return true;
}

#endif /* UTILS_H */
